/***  Estimate the J(∞), Ver 1.00, Date: 14010227 *****************************
 ***                                                                        ***
 ***  Copyleft (ɔ) F. Bolhasani 2020-22, All lefts reserved!                ***
 ***                                                                        ***
 ******************************************************************************

 * This code is under construction. It might contain some errors.
 * So you can try it with your own risk!
 */

#ifndef ESTJ_H

#define ESTJ_H

#include <eigen3/Eigen/Dense>
//#include <E:\code blocks\CodeBlocks\MinGW\include\eigen3\eigen-3.4.0\Eigen\Dense>

//* The coupling dyadic between two dipole with relative displacement r.
Eigen::Matrix3f couplingJ(const Eigen::Vector3f& r);

//* Following function gets the a and b as bases of the triangular Bravais lattice, and
//* calculates the J(∞). Then stores it in the 1st line of J_inf.csv text file.
void Store_Jinf(const Eigen::Vector3f& a, const Eigen::Vector3f& b);

#endif
