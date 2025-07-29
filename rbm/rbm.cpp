/***  Rotational Brownian Motion, Ver 1.2, Date: 17 May 2022 ******************
 ***                                                                        ***
 ***  Copyleft (ɔ) Nasim 2020-22, All lefts reserved!                       ***
 ***                                                                        ***
 ******************************************************************************

 * You can compile this code by the following command in the shell on a
 * single-core machine:
 * > g++ -o rbm rbm.cpp utils.cpp random.cpp vec.cpp -std=c++1z -Ofast
 *, then execute it in the shell by
 * > ./rbm
 

 * This code is under construction. It might contain some errors.
 * So you can try it at your own risk!
 */

//#define DEBUG_MODE                          // Activate debug mode
//#define NO_WAIT                             // Deactivate wait() at the end of code; see utils.h

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <omp.h>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>
#include "mtutils.h"
#include "random.h"
#include "utils.h"
#include "estJ.h"
#include "Binder.h"

using namespace std;
using namespace Eigen;

// Constants //
// ========= //
const int NR = 500;                          // Number of realization
const int L = 30;                           // L x L unit cell lattice
const int N = sqr(L);                       // Number of dipoles in the unit cell (supercluster).
const int NSC = 2;                        // Number of MNPs in a supercluster
const int ceq = 400;                        // Number of steps that are needed for approaching the equilibrium state.

const double muNP = 1.4e-15;                // The magnetic moment of one nanoparticle [J/T or A.m²/kg]
const double muSC = NSC * muNP;             // The magnetic moment of supercluster [J/T or A.m²/kg]
const double kB = 1.38e-23;                 // Boltzmann constant [J/K]

const float T = 310;                        // The human body temperature [K]
const float mu0 = 4 * pi * 1e-7;            // The magnetic permeability of vacuum [N/A²]
const float dt = 1. / 256;                  // Δt [τ_D]
const float l = 1.e-4;                      // Average distance between adjacent superclusters in meninges
const float l3 = pow(l, 3);                 // l³
const float aNP = 8.5e-8;                   // The average radius of nanoparticles = 85 * 10⁻⁹ [m]
const float eta = 0.69e-3;                  // Viscosity of cytoplasm [Pa.s]; 0.69 [mPa.s] for water in 37 ֯C
const float tmax = 1.e6;                     // Maximum of simulation time [τ_D]
const float zeta = NSC * 8 * pi *           // Random noise torque coefficient
                   pow(aNP, 3) * eta;
// λ is a unitless constant that compares magnetic energy with thermal fluctuation. The critical value of λ
const float lambdaC = 1/(0.33+0.61/log10(N));
const float lambdaMax = 12;                 // The maximum of λ
const float tauD = zeta / (2 * kB * T);     // Debye relaxation time, ζ/(2k_B T) [s]
const float m_lambda = 0.014                      // the slogan of variable lambda

const Vector3f BDC0(0, 0, 0);               // DC part of external magnetic field [B⁎]; in the initial part,
const Vector3f BDC1(1, 0, 0);               // and in the 2ⁿᵈ part of dynamics. note: 65 [µT] ~ 2100 [B⁎].
const Vector3f a(1, 0, 0),                  // Bases of the triangular Bravais lattice
               b(0.5, 0.5 * sqrt(3), 0);    // Maximum of simulation time [τ_D]


#define DATA 0
// If DATA == 1, the snapshots are recorded.

#define DYNAMICS 0
// If DYNAMICS == 0, the dynamics are simple without any change in external condition.
// If DYNAMICS == 1, the dynamics are continuing after lambdaMax up to tMax.

const static IOFormat CSVFormat(StreamPrecision, DontAlignCols, ", ", "\n");

// Variables
// =========
float t;                                    // Current time in the simulation [τ_D]
float lambda;                               // λ is a unitless constant which compares magnetic energy with
                                            // thermal fluctuation
float theta;                                // Angle of rotating magnetic field

Vector3f* r;                                // Position of dipoles [l]
Vector3f* mu;                               // Direction of magnetic moment of dipoles, where |μ[i]| == 1
BinderCumulant BC;                          // calculate the Binder's cumulant. It is gets samples and
                                            // calculated in execute()!
Matrix3f Jinf;                              // J(∞) = \lim_{R→∞} J(R)
Matrix3f** Jtilda;                          // Jtilda[i][j] shows the total coupling of the iᵗʰ
                                            // dipole with all jᵗʰ dipoles in any cells.
Matrix3f* dJ;                               // \delta J[i] shows the reminder of interaction between
                                            // the iᵗʰ dipole and the entire lattice out of the constant
                                            // radius R in init().
Vector3f* BT;                               // Bₜ[i] shows the total magnetic field at rᵢ [B⁎]

Vector3f BDC;                              // DC part of external magnetic field [B⁎].

// File stream
// ============
ofstream snapshot;                          // The position and magnetic moment of all particles are stored in
                                            // the snapshot stream with the dict. format.
ofstream res;                               // The result of simulation

// ===== //
void init();                                // Common initialization
void done();                                // Common finalization

void init(int rI);                          // Initializing the rIᵗʰ realization
void done(int rI);                          // Finalization of rIᵗʰ realization

Vector3f mu_avg();                          // Average of 〈μᵢ〉
void calcBTotal();                          // calculates the total magnetic field by using the coupling tensor in
                                            // the unit cell and mean field for the remainder of the lattice. Then
                                            // it updates Bₜ[].
float magEnergy();                          // calculates the total magnetic energy.
void execute();                             // approaching to equilibrium

// simulates the system and changes λ from 0 to λₘₐₓ
void execute(float lambda1);

// simulates the system and increases λ from 0 to λₘₐₓ, where rI is a realization index.
void execute(int rI);

// Simulates a single hysteresis loop, where λ₀ = 3λc, ΔB shows the linear changes
// in the external magnetic field in each step of simulation, B₀ shows the maximum
// amplitude of external magnetic field, and rI is a realization index.
void executeHysteresis(int rI, const Vector3f dB, const float B0 = 1, const float lambda0 = 3*lambdaC);

// simulates a rotational external magnetic field, where B₀ shows
// the amplitude of the magnetic field and rI is a realization index.
void executeRotationalB(int rI, const float B0 = 1);

void executeSingleStep();                   // executes a single time step.
void exportHeader();                        // exports the header to the snapshot stream
                                            // means exclude header.
void exportResult(int id);                  // exports the current state to the res stream. θ shows the angle
                                            // of external magnetic field.
void exportSnapshot(int id);                // exports the current state to the snapshot stream,
                                            // where id is the index of data block.

// functions definition //
// ==================== //
int main (int argc, char *argv[]) { // Main routine

    lout << "\nRotaional Brownian Motion, Ver 1.22\n"
         << "Copyleft (ɔ) F. Bolhasani 2020-22, All lefts reserved!\n"
         << "Date: 14010302" << endl;

    init_mtutils(10);                        // initiates the OpenMP
    // Note: Due to the simultaneous use of the SSE instruction set and OpenMP, and the competition between
    // the SSE instructions set and the separate cores in using the floating-point units and cache, defining
    // the maximum allowed value for the number of CPU cores in OpenMP may not be the best choice due to some
    // overloads. The appropriate amount depends on the number of actual floating units available and the size of
    // cache. For cheap processors, half of the number of CPU cores might be enough!

    // Randomize the pseudo-random number generator
    randomize();
    lout << "\nseed: " << seed << endl;

    // manage the input switches
    if ((argc == 2) && (string(argv[1]) == "-Jinf"))
        Store_Jinf(a, b);

    if (!IsFileExist("J_inf.csv"))
        Store_Jinf(a, b);

    // loads the estimation of J₁₁(∞) which is estimated by the subroutine Store_Jinf().
    ifstream J_inf("J_inf.csv", std::ios_base::in);

    // Reads the J₁₁(∞) from J_inf.txt
    float J;
    J_inf >> J;

    // and initializes the Jinf.
    Jinf << J, 0, 0,
            0, J, 0,
            0, 0, -2 * J;

    // Introducing the parameters before beginning
    lout << "unit cell: " << L << " x " << L << "\tNᵣ: " << NR
         << "\nT: "  << T << " [K]\t\tDC part of Bₑₓₜ: (" << BDC.transpose().format(CSVFormat) << ") [B⁎]"
         << "\na: (" << a.transpose().format(CSVFormat) << ")\t\tb: (" << b.transpose().format(CSVFormat) << ')'
         << setprecision(3)
         << "\nτD: " << tauD << " [s]\t\tμSC: " << muSC << " [J/T or A.m²/kg]"
         << "\nl: "  << l << "\t\tλc: " << lambdaC
         << "\nb0 (intercept colding lambda): " << 1/(1.2 * N + 465.8)
         << "\nm (slope for colding lambda): " << m_lambda  << endl;

    // calculates the executing time of the main section of code.
    lout.start();

    // initialization
    init();

    for (int r = 1; r <= NR; r++) { // A realization loop

        init(r);

        // The following line could be used in the remote SSH running!!!
        lout.echo(false);

        // Uncomment one of the following lines according to the simulation plan: //
        execute(r);
        //executeHysteresis(r, Vector3f(0.01, 0, 0), 1);
        //executeRotationalB(r, 1);

        // The following line could be used in the remote SSH running!!!
        lout.echo(true);

        done(r);

 	    lout << "Execution of the " + to_string(r) + "ᵗʰ realization is Finished!" << endl;
    }

    done();

    // calculates the executing time of the main section of code.
    lout.stop();

    lout << "Finish!" << endl;

    wait();

    free_mtutils();

    return 0;
}

void init() { // Common initialization of all realizations

    r  = new Vector3f[N];
    mu = new Vector3f[N];
    BT = new Vector3f[N];
    dJ = new Matrix3f[N];

    // Initializing the lattice points
    int k = 0;
    for (int i = 0; i < L; i++)
        for (int j = 0; j < L; j++)
            r[k++] = i * a + j * b;

    if ( L <= 3) { // Following lines show points of a small lattice
        int k = 0;
        for (int i = 0; i < L; i++)
            for (int j = 0; j < L; j++) {
                lout << "i: " << i << '\t'
                     << "j: " << j << '\t'
                     << "ia + jb = [" << r[k++].transpose().format(CSVFormat) << ']' << endl;
            }
    }
    // Jtilta is calculated for a triangular lattice of radius R
    const int R = 500;
    const float RMax = R * sin(pi/3);

    // Allocating the temporary memory for double precision dJtilda
    Matrix3d** dJtilda  = new Matrix3d*[N];
    for (int i=0; i < N; i++) {
        dJtilda[i] = new Matrix3d[N];
        for (int j=0; j < N; j++)
            dJtilda[i][j] = Matrix3d::Zero();
    }

    // Computing the couplings with double precision in dJtilda[][]
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = -R/L; k <= R/L; k++)
                for (int l = -R/L; l <= R/L; l++) {
                    Vector3f d = r[j] - r[i] + L*k*a + L*l*b;

                    // Increase the symmetry of calculation
                    if ( d.squaredNorm() <= RMax )
                        dJtilda[i][j] += couplingJ( d ).cast<double>();
                }

    // Assign dJtilda[][] to Jtilda[][]
    Jtilda  = new Matrix3f*[N];
    for (int i = 0; i < N; i++) {
        Jtilda[i] = new Matrix3f[N];
        for (int j = 0; j < N; j++)
            Jtilda[i][j] = dJtilda[i][j].cast<float>();
    }

    // Calculating the difference of Jtilda and J(∞) and assign it to dJ[]
    for (int i = 0; i < N; i++) {
        Matrix3d JTotal = Matrix3d::Zero();
        for (int j = 0; j < N; j++)
            JTotal += dJtilda[i][j];
        dJ[i] = Jinf - JTotal.cast<float>();
    }

    // Deallocating the temporary memory of dJtilda
    for (int i = 0; i < N; i++)
        delete[] dJtilda[i];
    delete[] dJtilda;
}

void done() { // Common finalization

    delete[] r;
    delete[] mu;
    delete[] BT;
    delete[] dJ;

    for (int i = 0; i < N; i++)
        delete[] Jtilda[i];
    delete[] Jtilda;
}

void init(int rI) { // Initializing the rIᵗʰ realization

    t = 0;
    lambda = 0.1;
    // First value of changing angle
    theta = 0;
    // DC magnetic field in the 1ˢᵗ part of dynamics.
    BDC = BDC0;

    // Initializing {μᵢ} with random direction
    for (int i = 0; i < N; i++) {
        mu[i] = rndDir();
    }
    // Initial value of Binder cumulant.
    BC.init();

    #if DATA == 1
        snapshot.open("snapshot" + to_string(rI) + ".txt", std::ios_base::out | std::ios_base::trunc);
        exportHeader();
    #endif

    res.open("result" + to_string(rI) + ".txt", std::ios_base::out | std::ios_base::trunc);
    res << setprecision(3) << "{" << "\"result\": {" << endl;
}

void done(int rI) { // Finalization of rIᵗʰ realization

    #if DATA == 1
        snapshot.close();
    #endif

    res.close();
}

Vector3f mu_avg() { // Average of 〈μᵢ〉

    Vector3f S = Vector3f::Zero();
    for (int i = 0; i < N; i++)
        S += mu[i];

    return S / N;
}

void calcBTotal() { // calculates the total magnetic field by using the coupling tensor in the unit cell
                    // and mean field for the remainder of the lattice. Then it updates Bₜ[].

    const Vector3f mu_MF = mu_avg();

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        // Total net magnetic field produced by dipoles at rᵢ
        Vector3f BDs = Vector3f::Zero();

        for (int j = 0; j < N; j++) {
            BDs += Jtilda[i][j] * mu[j];
        }
        BT[i] = BDC + lambda * (BDs + dJ[i] * mu_MF);
    }
}

float magEnergy() { // calculates the total magnetic energy.

    double S = 0;
    //#pragma omp parallel for reduction (+: S) WHY?

    for(int i = 0; i < N; i++)
        // S -= mu[i].dot(BDC) + 0.5 * mu[i].dot(BT[i] - BDC);
        // Current line multiple 0.5 is derived from the previous equation.
        S -= mu[i].dot(BDC + BT[i]);

    S *= 0.5;

    return S / (N * lambda);
}

void executeSingleStep() { // executes a single time step.

    calcBTotal();

    #pragma omp parallel for
    for (int i = 0; i < N; i++) { // The following loop evaluates μ^{(n+1)} White Gaussian 3d noise

        Vector3f W(rndN(), rndN(), rndN());
        mu[i] +=  0.5 * dt * ( BT[i] - mu[i].dot(BT[i]) * mu[i] ) + // Note: |μ[i]| == 1
                  sqrt(dt) * W.cross(mu[i]);

// Normalize mu
        mu[i].normalize();
    }
    t += dt;
}

void execute() { // approaching to equilibrium
    for (int c = 0; c < ceq; c++)
        executeSingleStep();
}

void execute(float lambda1) { // simulates the system and changes λ from 0 to λ₁.

    while (lambda < lambda1) {
        execute();

            //lambda += b0 + m * |lambda - lambdaC|;

            //lambda += 1/(489.16 + 1.3 N) +
            //          1/(40.35 + 0.73 L) * fabs(lambda - lambdaC);

           lambda += 1/(1.2 * N + 465.8)
                     m_lambda * fabs(lambda - lambdaC);

        lout << prog << "t = " << fixed << setprecision(2) << t << "\tλ = " << lambda;
    }
    // for being sure in the end that lambda is equal to λ₁.
    lambda = lambda1;
    execute();
}

void execute(int rI) { // simulates the system and increase λ from 0 to λₘₐₓ,
                       // where rI is a realization index.
    #if DATA == 1
        exportSnapshot(1);
        int cSnapshot = 2;
    #endif

    int c = 1;
    int cRes = 1;
    exportResult(cRes++);

    while (lambda < lambdaMax) { // changes λ from 0 to λₘₐₓ

        executeSingleStep();
        // 〈μᵢ〉
        Vector3f M1 = mu_avg();
        BC.sample(M1.squaredNorm());

        if (c % ceq == 0) { // wait for equilibrium; ceq Δt ~ relaxation time?

            res << "," << endl;
            exportResult(cRes++);

            //lambda += b0 + m * |lambda - lambdaC|;
            //lambda += 1/(489.16 + 1.3 N) +
            //          1/(40.35 + 0.73 L) * fabs(lambda - lambdaC);

            lambda += 1/(1.2 * N + 465.8)
                     m_lambda * fabs(lambda - lambdaC);

        }
        #if DATA == 1
            if (c % 40 == 0) {
                snapshot << "," << endl;
                exportSnapshot(cSnapshot++);
            }
        #endif
        c++;
        lout << prog << fixed << setprecision(2)
             << "t = "       << t
             << "\tλ = "     << lambda
             << "\t〈μᵢ〉 = (" << M1.transpose().format(CSVFormat) << ")       ";
    }

    #if DYNAMICS == 1

        lambda = lambdaMax;

        for (int i = 0; i < ceq; i++) { // last step of λ to λ_max
        executeSingleStep();

        #if DATA == 1
            if (c % 40 == 0) {
                snapshot << "," << endl;
                exportSnapshot(cSnapshot++);
            }
        #endif

        c++;

        lout << prog << fixed << setprecision(2) << "t\t"<< t;
        }

        lout << "\n\nThe system reaches to the critical point.\n"
            << "Now, the external field is turned on!" << endl;

        // The DC magnetic field in 2ⁿᵈ part of dynamics.
        BDC = BDC1;

        lout << fixed << setprecision(4)
            << "t = " << t << "\tB_DC = ("
            << resetiosflags(std::ios_base::floatfield | std::ios_base::showpoint)
            << setprecision(-1)                // resets the stream format
            << BDC.transpose().format(CSVFormat) << ")\n" << endl;

        BC.init();

        while (t < tmax) { // dynamics of the system at λ_max
            executeSingleStep();

            // 〈μᵢ〉
            Vector3f M1 = mu_avg();
            BC.sample(M1.squaredNorm());

            // wait for equilibrium; ceq Δt ~ relaxation time?
            if (c % ceq == 0){
                res << "," << endl;
                exportResult(cRes++);

            #if DATA >= 2
            if ((c % 40 == 0) && (lambda > 0) && (rI == 1)) {
                snapshot << "," << endl;
                exportSnapshot(cSnapshot++);
            }
            #endif
            }

            c++;

            lout << prog << fixed << setprecision(2)
                << "t = "       << t
                << "\tλ = "     << lambda
                << "\t〈μᵢ〉 = (" << M1.transpose().format(CSVFormat) << ")       ";
        }

    #endif  // DYNAMICS == 1

    #if DATA == 1
        snapshot << "}}" << endl;
    #endif

    res << "}}" << endl;
    lout << '\n' << endl;
}

void executeHysteresis(int rI,
                       const Vector3f dB,     // linear changes in the external magnetic field in each step of
                       const float B0,        // simulation, B₀ shows the amplitude of magnetic field, and rI
                       const float lambda0) { // is a realization index.

    // Hysteresis loop has 3 sections, 0: B = [0, B₀], 1: B = [B₀, -B₀], 2: B = [-B₀, B₀].
    int loop_counter = 0;
    // to change direction of changing external B
    int sign = +1;
    // fixed lambda, first point
    lambda = lambda0;
    // counter to saving results.
    int cRes = 1;
    exportResult(cRes++);

    while (loop_counter < 3) {

        execute();

        res << "," << endl;
        exportResult(cRes++);

        BDC += sign * dB;

        if ( BDC.norm() > B0 ) { // to prevent BDC to exceed the max/min value
            loop_counter++;
            sign *= -1;
        }
        lout << prog << fixed << setprecision(2)
             << "time = " << t
             << "\tB = (" << BDC.transpose().format(CSVFormat) << ')';
    }
    res << "}}" << endl;

    lout << endl;
}

void executeRotationalB(int rI, const float B0) { // simulates a rotational external magnetic field, where B₀ shows
                                                  // the amplitude of magnetic field and rI is a realization index.
    // ΔB
    const float dB = 0.01;
    // Δθ
    const float deltaTheta = 0.01 * pi;

    // At first system must be at the critical point.
    execute(lambdaC);

    while (BDC.x() <= B0) {

        execute();
        BDC.x() += dB;

        lout << prog << fixed << setprecision(2)
             << "t = " << t
             << "\tB = (" << BDC.transpose().format(CSVFormat) << ')';
    }
    int cRes = 1;
    float theta = 0;

    // Simulating the rotating magnetic field, and simultaneously export the results.
    while (theta <= 2 * pi ) {
        BDC = Vector3f(cos(theta), sin(theta), 0);

        execute();

        if (cRes > 1)
            res << "," << endl;
        exportResult(cRes++);


        theta += deltaTheta;

        lout << prog << fixed << setprecision(2)
             << "t = " << t
             << "\tB = (" << BDC.transpose().format(CSVFormat) << ')';
    }
    res << "}}" << endl;

    lout << endl;
}

void exportHeader() { // exports the header to the snapshot stream

    snapshot << fixed << setprecision(3);

    // Header of the snapshot file
    snapshot << "{\n"
             << "\"lattice\": {\n"
             << "\"items\": " << N << ",\n"
             << "\"lacations\": [" << endl;

    for (int i = 0; i < N; i++) {
        snapshot << "\"(" << r[i].transpose().format(CSVFormat) << ")\"";

        if (i != N - 1)
            snapshot << ",\n";
    }
    snapshot << "]}\n,\n"
             << "\"snapshot\": {" << endl;
}

void exportResult(int id) { // exports the current state to the res stream.

    Vector3f mu = mu_avg();

    res << "\"" << id << "\": {\n"
        << "\"items\": " << N << ",\n"
        << "\"lambda\":" << lambda << ",\n"
        << "\"time\":"   << t << ",\n"
        << "\"theta\":"  << theta << ",\n"
        << "\"Total Magnetic Energy\":" << magEnergy() << ",\n"
        << "\"Magnetization\": "  << mu.norm() << ",\n"
        << "\"Binder Cumulant\": " << BC.BC(true) << ",\n"
        << "\"B.x\": " << BDC.x() << ",\n"
        << "\"B.y\": " << BDC.y() << ",\n"
        << "\"B.z\": " << BDC.z() << ",\n"
        << "\"Mp\": " << sqrt(sqr(mu.x()) + sqr(mu.y())) << ",\n"
        << "\"Mx\": " << mu.x() << ",\n"
        << "\"My\": " << mu.y() << ",\n"
        << "\"Mz\": " << mu.z() << "}" << endl;
}

void exportSnapshot(int id) { // exports the current state to the snapshot stream

    snapshot << "\"" << id << "\": {\n"
             << "\"items\": " << N << ",\n"
             << "\"lambda\":" << lambda << ",\n"
             << "\"time\":"   << t << ",\n"
             << "\"Energy\":" << magEnergy() << ",\n"
             << "\"data\": [\n";

    for (int i = 0; i < N; i++) {
        snapshot << "\"(" << mu[i].transpose().format(CSVFormat) << ")\"";
        if (i != N - 1)
            snapshot << "," << endl;
    }
    snapshot << "]}" << endl;
}
