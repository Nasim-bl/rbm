/***  Estimate the J(∞), Ver 1.00, Date: 22 May 2022 **************************
 ***                                                                        ***
 ***  Copyleft (ɔ) Nasim 2020-22, All lefts reserved!                       ***
 ***                                                                        ***
 ******************************************************************************

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
#include <eigen3/Eigen/Dense>
#include "utils.h"
#include "estJ.h"

using namespace std;
using namespace Eigen;

// Constants
// =========
const int N = 30;                           // The maximum radius of circle which includes dipoles is ~10N.

const static IOFormat CSVFormat(StreamPrecision, DontAlignCols, ", ", "\n");

double estimation(int R, int& count,        // Estimate the J(∞), where a and b are the bases of the Bravais
                  const Vector3f& a,        // lattice, and count returns number of dipoles included in the
                  const Vector3f& b);       // estimation.

Matrix3f couplingJ(const Vector3f& r) { // The coupling dyadic between two dipoles with relative displacement r.
    /** The coupling dyadic is defined as,
     * \f[\stackrel{\scriptstyle\leftrightarrow}{\mathbf{J}}(\mathbf{r}) = \left\{
     * \begin{array}{ll}
     * \displaystyle\frac{ 3\mathbf{r}\mathbf{r} - |\mathbf{r}|^2 \mathrm{I}_{3\times3} } {|\mathbf{r}|^5} & \mathbf{r}| > 0,\\
     * \mathrm{O}_{3\times3} & |\mathbf{r}| = 0
     * \end{array}
     * \right.\f]
     * This function is optimized to speed up the evaluation of the coupling dyadic more than 3 times.
     * The body of the function before optimization:
     * const float r2 = norm2(r);
     * if ( r2 > 0.1e-7 )
     *     return ( 3*Dyadic(r) - r2 * I3x3 ) / ipow(norm(r), 5);
     * else
     *     return O3x3;*/
    static const float eps = 1e-7;
    const float r2  = r.squaredNorm();
    if ( r2 > eps ) {                       // self-interaction of dipoles is omitted
        const float x = 1 / (sqr(r2) * sqrt(r2)); // x = |r|^{-5}

        return ( 3 * r * r.transpose() - r2 * Matrix3f::Identity() ) * x;
    } else
        return Matrix3f::Zero();
}

// Following function gets the a and b as bases of the triangular Bravais lattice, and
// calculates the J(∞). Then stores it in the 1st line of J_inf.csv text file.
void Store_Jinf(const Vector3f& a, const Vector3f& b) {
    lout << "\nEstimating J(∞) ..." << endl;

    ofstream res("J_inf.csv",               // The result of estimation
                 std::ios_base::out | std::ios_base::trunc);

    lout.start();                           // calculates the executing time of the
                                            // main section of code.
    double J11[N];
    int count[N];
    double Sx  = 0,                         // used for the linear fit
           Sy  = 0,
           Sxy = 0,
           Sx2 = 0;

    for (int i=0; i < N; i++) {
        int R = 10*(i+1);
        J11[i] = estimation(R, count[i], a, b);

        float x = 1. / R;
        Sx  += x;
        Sx2 += sqr(x);
        Sxy += x * J11[i];
        Sy  += J11[i];
    }

    Sx  /= N;
    Sy  /= N;
    Sxy /= N;
    Sx2 /= N;

    double slope = ( Sxy - Sx*Sy ) / ( Sx2 - sqr(Sx) );
    double intercept = Sy - slope * Sx;

    lout << "\nJ₁₁(∞) = " << fixed << setprecision(5) << intercept << '\n' << endl
         << resetiosflags(std::ios_base::floatfield | std::ios_base::showpoint)
         << setprecision(-1);               // resets the stream format

    res  << intercept << endl;
    res << "R, 1/R, N, J(R)" << endl;
    for (int i=0; i < N; i++) {
        int R = 10*(i+1);
        res << R << ", " << 1./R << ", " << count[i] << ", " << J11[i] << '\n';
    }
    res.flush();

    lout << "Finish estimating J(∞), ";
    lout.stop();                            // calculates the executing time
}

// Following function estimates the J(∞), where a and b are the bases of the Bravais lattice, and count returns
//number of dipoles included in the estimation.
double estimation(int R, int& count, const Vector3f& a, const Vector3f& b) {
    count = 0;
    Matrix3d JTotal = Matrix3d::Zero();

    for (int i = -2*R; i<2*R; i++)
        for (int j = -2*R; j<2*R; j++) {    // Total coupling of the circular area
            if ( (i == 0) && (j == 0) ) continue;

            const Vector3f r = i * a + j * b;

            if ( r.norm() <= R ) {
                JTotal += couplingJ(r).cast<double>(); // only includes the symmetrical circular area with radius of 10n.
                ++count;
            }
        }
    lout << "\nJₜ(R = " << R << "): [\n"
         << fixed << setprecision(3) << JTotal.format(CSVFormat) << "]" << endl;

    return JTotal(1,1);
}
