/** Thread Safe Pseudo Random Number Generator (PRNG), Ver 2.00, Date: 1400-12-20
 *
 * @file random2.h
 * @author O. Farzadian, A. Goodarzinick, F. Bolhasani, and M. D. Niry (m.d.niry at iasbs.ac.ir)
 * @version 2.00
 * @date 2022-03-11
 *
 * @copyright Copyleft (ɔ) 2013-22; All lefts reserved!
 *
 * **Abbrevation**
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

#ifndef RANDOM_H

#define RANDOM_H

extern long seed;                           ///< The default global seed of the PRNG
#ifdef _OPENMP
  #pragma omp threadprivate(seed)           // This line makes the seed variable a threadsafe variable; each thread
                                            // has its own copy of the variable.
#endif

//BEGIN_FOLD - Part of the code from the Numerical Recipes in C, chapter 7. ...
/// @cond INTERNAL_DECLARATION
// hide the following part of the code from doxygen documentation system.

/* This is a 32-bit PRNG with uniform distribution in the range [0..1),
 * which is implemented in the Numerical Recipes in C, chapter 7.
 *
 * Long period (\f$> 2 × 10^{18}\f$) PRNG of L. Ecuyer with Bays-Durham shuffle and added safeguards. Returns
 * a uniform random number deviate between 0.0 and 1.0 (exclusive of the endpoint values).
 *
 * @attention Call with idum a negative integer to initialize; thereafter, do not alter
 * idum between successive deviates in a sequence. RNMX should approximate the largest floating
 * value, which is less than 1.
 *
 * Visit www.nr.com for the license.*/
double ran2(long *idum);

/* returns a normally distributed number deviate with zero mean and unit variance, using `ran2(idum)`
 * as the source of uniform deviates. `gasdev()` implemented in the Numerical Recipes in C, chapter 7.
 *
 * idum is the seed of ran2() PRNG.
 *
 * Visit www.nr.com for the license.*/
double gasdev(long *idum);

/// @endcond
//END_FOLD - Visit www.nr.com for the license.

/** @name randomize(...)
 * @details The following function initiates the default global seed of the PRNG. It is a threadsafe function.
 * Some functions of this library use the argument called idum as a seed of the PRNG. If this argument is
 * not available, the global default seed is used.
 *
 * if seed0 is available, `randomize()` renews the default global seed in multi-thread mode to seed0. This
 * option is useful in debug mode!
 @{*/
void randomize();                           ///< @details initiates the default global seed of the PRNG.
void randomize(int seed0);                  ///< @details renews the default global seed in multi-thread mode to seed0.
///@}

/** @name rndN(...)
 * @details The following function returns a random number with the standard normal (Gaussian) distribution.
 * if idum is not provided the default global seed is used.
 @{*/
/// @details generates a normally distributed number deviate with zero mean and unit variance.
inline double rndN() { return gasdev(&seed); }
/** @details generates random numbers with the standard normal (Gaussian) distribution where the average and
 * variance are mean and stdev\f$\!^2\f$, respectively.*/
inline double rndN(double mean, double stdev) { return mean + stdev * gasdev(&seed); }
/** @details generates a normally distributed number deviate with zero mean and unit variance. idum is a seed
 * of the PRNG.*/
inline double rndN(long& idum) { return gasdev(&idum); }
/** @details generates random numbers with the standard normal (Gaussian) distribution where the average and
 * variance are mean and stdev\f$\!^2\f$, respectively. idum is a seed of the PRNG.*/
inline double rndN(double mean, double stdev, long& idum) { return mean + stdev * gasdev(&idum); }
///@}

/** @name rnd(...)
 * @details The following function generates a uniformly distributed random numbers. By default, random numbers
 * are in the in the half-open interval [0,1).
 *
 * If integer N is provided, the function returns discrete integer random numbers in the interval [0,N).
 *
 * If min and max are provided, it returns random numbers in the interval [min,max).
 * @note To force the compiler to use the floating-point version of the function, you can use the phrase
 * "<double>" after the name of the function; _e.g._, `double r = Random<double>(1., 10.);`
 *
 * If idum is not provided the default global seed is used.
 @{*/
/// generates a random number with a uniform distribution in the interval [0,1).
inline double rnd() { return ran2(&seed); }
/** generates a random number with a uniform distribution in the interval [0,1).
 * @details idum is a seed of the PRNG.*/
inline double rnd(long& idum) { return ran2(&idum); }

/// generates a random number with a uniform distribution in the integer interval [0,N).
inline int rnd(int N) { return int(ran2(&seed)*N); }
/** generates a random number with a uniform distribution in the integer interval [0,N).
 * @details idum is a seed of the PRNG.*/
inline int rnd(int N, long& idum) { return int(ran2(&idum)*N); }

/** generates a random number with the uniform distribution in the interval [min,max).
 * @note To force the compiler to use the floating-point version of the function,  you can use the phrase
 * "<double>" after the name of the function; _e.g._, `double r = Random<double>(1., 10.);`*/
inline double rnd(double min, double max) { return min + ran2(&seed)*(max-min); }
/** generates a random number with the uniform distribution in the interval [min,max).
 * @details idum is a seed of the PRNG.
 * @note To force the compiler to use the floating-point version of the function,  you can use the phrase
 * "<double>" after the name of the function; _e.g._, `double r = Random<double>(1., 10.);`*/
inline double rnd(double min, double max, long &idum) { return min + ran2(&idum)*(max-min); }
/// generates a random number with the uniform distribution in the interval [min,max).
inline int rnd(int min, int max) { return int(min + ran2(&seed)*(max-min)); }
/** generates a random number with the uniform distribution in the interval [min,max).
 * @details idum is a seed of the PRNG.*/
inline int rnd(int min, int max, long &idum) { return int(min + ran2(&idum)*(max-min)); }
///@}

/** @name rndDir()
 * @details The following function returns a unit vector with a random direction.
 *
 * @note This function is only defined, if The `Eigen' library is included in the coded before `random2.h'.
 */
#ifdef EIGEN_CORE_H
inline Eigen::Vector3f rndDir() { ///< returns a unit vector with a random direction
    Eigen::Vector3f v;
    do {
        v = Eigen::Vector3f(2 * rnd() - 1,
                            2 * rnd() - 1,
                            2 * rnd() - 1);
    } while ( v.squaredNorm() > 1. );

    return v.normalized();
}
#endif


#endif
