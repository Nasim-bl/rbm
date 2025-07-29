/** Implementation of the thread Safe Pseudo Random Number Generator (PRNG), Ver 2.00, Date: 1400-12-20
 *
 * @file random2.cpp
 * @author O. Farzadian, A. Goodarzinick, F. Bolhasani, and M. D. Niry (m.d.niry at iasbs.ac.ir)
 * @version 2.00
 * @date 2022-03-11
 *
 * @copyright Copyleft (ɔ) 2013-22; All lefts reserved!
 *
 * **Abbreviation**
 *
 * Pseudo Random Number Generator (PRNG)
 *
 * @section DESCRIPTION
 *
 * The functions and routines in this library provides facilities to generate random numbers. They are based on
 * the functions
 *
 *     double ran2(long *idum);
 *
 * and
 *
 *     double gasdev(long *idum);
 *
 * which are implemented in the Numerical Recipes in C, chapter 7.
 *
 * `ran2()` is a long period (\f$> 2 × 10^{18}\f$) random number generator of L. Ecuyer with Bays-Durham shuffle
 * and added safeguards. Returns a uniform random deviate between 0.0 and 1.0 (exclusive of the endpoint values).
 *
 * \attention Call `randomize()` to initiates the default global seed or call functions with idum a negative
 * integer to initialize; thereafter, do not alter idum or seed between successive deviates in a sequence.
 *
 * @note Code should be compiled with -fopenmp switch of g++ to use an OpenMP mode.
 *
 * @section LICENSE
 *
 * The functions and routines in the library are based on the pseudo random number generators (PRNGs) `ran2()`
 * and `gasdev()`, which are implemented in the Numerical Recipes in C, chapter 7.
 *
 * Visit www.nr.com for the lenience.
 *
 * Reminder of codes in the library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * It is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the library. If not, see <https://www.gnu.org/licenses/>.
 *
 * @section REFERENCE
 *
 * [1] W. H. Press, S. A. Teukolsky, W. T. Vetterling, and B. P. Flannery, Numerical recipes 3rd edition: The
 * art of scientific computing (Cambridge University Press, 2007).
 */

#include <ctime>
#include <cmath>
#ifdef _OPENMP // Use omp.h if -fopenmp is used in g++
    #include <omp.h>
#endif
#include "random.h"

using namespace std;

// Implementation of the library
// =============================

long seed = -36;                            // The default global seed of the PRNG
#ifdef _OPENMP
    #pragma omp threadprivate(seed)         // This line makes the seed variable a threadsafe variable; each
                                            // thread has its own copy of the variable.
#endif

/** @name randomize(...)
 * @details The following function initiates the default global seed of the PRNG. It is a threadsafe function.
 * Some functions of this library use the argument called idum as a seed of the PRNG. If this argument is
 * not available, the global default seed is used.
 *
 * if seed0 is available, `randomize()` renews the default global seed in multi-thread mode to seed0. This
 * option is useful in debug mode!
 @{*/
void randomize() { // initiates the default global seed of the PRNG.
    #ifdef _OPENMP
        #pragma omp parallel
        { seed = -abs(time(NULL) + omp_get_thread_num()); }
    #else
        seed = -abs(time(NULL));
    #endif
}
void randomize(int seed0) { // renews the default global seed in multi-thread mode to seed0.
    #ifdef _OPENMP
        #pragma omp parallel
        { seed = -abs(abs(seed0) + omp_get_thread_num()); }
    #else
        seed = -abs(seed0);
    #endif
}
///@}

//BEGIN_FOLD - Part of the code from the Numerical Recipes in C, chapter 7. ...
/// @cond INTERNAL_DECLARATION
// hide the following part of the code from doxygen documentation system.

/* returns a normally distributed number deviate with zero mean and unit variance, using `ran2(idum)`
 * as the source of uniform deviates. `gasdev()` implemented in the Numerical Recipes in C, chapter 7.
 *
 * idum is the seed of ran2() PRNG.
 *
 * Visit www.nr.com for the license.*/
double gasdev(long *idum) {
    static int iset = 0;
    static double gset;
    #ifdef _OPENMP                          // These lines make iset and gset threadsafe variables; each thread
                                            //  has its own copy of these variables.
        #pragma omp threadprivate(iset, gset)
    #endif

    if (*idum < 0) iset = 0;                // Reinitialize

    if  (iset == 0) {                       // We don’t have an extra deviate handy, so
        double fac, rsq, v1, v2;

        do {
            v1 = 2.0*ran2(idum) - 1.0;      // pick two uniform numbers in the square extending
            v2 = 2.0*ran2(idum) - 1.0;      // from -1 to +1 in each direction,
            rsq = v1*v1 + v2*v2;            // see if they are in the unit circle,
        } while (rsq >= 1.0 || rsq == 0.0); // and if they are not, try again.

        fac = sqrt(-2.0*log(rsq)/rsq);      // Now make the Box-Muller transformation to get two normal deviates. Return
        gset = v1*fac;                      // one and save the other for next time in gset.
        iset = 1;
        return v2*fac;
    } else {                                // We have an extra deviate handy, so
        iset = 0;                           // unset the flag,
        return gset;                        // and return it.
    }
}

/* This is a 32-bit PRNG with uniform distribution in the range [0..1),
 * which is implemented in the Numerical Recipes in C, chapter 7.
 *
 * Long period (> 2 × 10^{18}) PRNG of L. Ecuyer with Bays-Durham shuffle and added safeguards. Returns
 * a uniform random number deviate between 0.0 and 1.0 (exclusive of the endpoint values).
 *
 * @attention Call with idum a negative integer to initialize; thereafter, do not alter
 * idum between successive deviates in a sequence. RNMX should approximate the largest floating
 * value, which is less than 1.
 *
 * Visit www.nr.com for the license.*/
#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

double ran2(long *idum) {
    int j;
    long k;
    static long idum2 = 123456789;
    static long iy    = 0;
    static long iv[NTAB];
    double temp;
    #ifdef _OPENMP                          // These lines make idum2, iy, and iv threadsafe variables;
                                            // each thread has its own copy of these variables.
        #pragma omp threadprivate(idum2, iy, iv)
    #endif

    if (*idum <= 0) {                       // Initialize
        if (-(*idum) < 1) *idum=1;          // Be sure to prevent idum = 0
        else *idum = -(*idum);
        idum2=(*idum);
        for (j=NTAB+7;j>=0;j--) {           // Load the shuffle table (after 8 warm-ups)
            k=(*idum)/IQ1;
            *idum=IA1*(*idum-k*IQ1)-k*IR1;
            if (*idum < 0) *idum += IM1;
            if (j < NTAB) iv[j] = *idum;
        }
        iy=iv[0];
    }

    k=(*idum)/IQ1;                          // Start here when not initializing
    *idum=IA1*(*idum-k*IQ1)-k*IR1;
    if (*idum < 0) *idum += IM1;
    k=idum2/IQ2;
    idum2=IA2*(idum2-k*IQ2)-k*IR2;
    if (idum2 < 0) idum2 += IM2;
    j=iy/NDIV;
    iy=iv[j]-idum2;
    iv[j] = *idum;
    if (iy < 1) iy += IMM1;
    if ((temp=AM*iy) > RNMX) return RNMX;   // Because users don’t expect endpoint values
    else return temp;
}

#undef IM1
#undef IM2
#undef AM
#undef IMM1
#undef IA1
#undef IA2
#undef IQ1
#undef IQ2
#undef IR1
#undef IR2
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX

/// @endcond
//END_FOLD - Visit www.nr.com for the license.
