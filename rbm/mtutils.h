/******************************************************************************/
/*** General Multi-thread Utility                                           ***/
/*** Ver 0.92                                                               ***/
/*** Date: 17 Oct. 2019                                                     ***/
/*** Copyleft (c) 2015 by Abdorreza Goodarzinick and M. Delbari, All lefts  ***/
/*** reserved.                                                              ***/
/*** Licensed under The GNU General Public License v3.0                     ***/
/*** Code implemented in GNU C++ compiler (v. 4.6.3) in 64-bit UBUNTU 12.04 ***/
/*** Run under a Intel® Core™ i3-2330M CPU @ 2.20GHz × 4 machine with 2 GB  ***/
/*** RAM.                                                                   ***/
/******************************************************************************/

/*
/* OpenMP Note:
  Code should be compiled with the -fopenmp switch of gcc.
*/

#ifndef MTUTILS_H

#define MTUTILS_H

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

// Thread Variables
extern int N_CPU;                           // Shows the number of CPU cores which is used


//------------------------------------------------------------------------------
// threadlog

// Separate log file for each thread with 'thread#.log'. Threadlog should be used in the multi-threaded section of code
// when you want to send logs to the related log file.
extern std::ofstream threadlog;
#pragma omp threadprivate(threadlog)        // This line makes threadlog threadsafe variable; each thread has
                                            // its copy of the variable.

void init_mtutils(int NCore=-1);            // Initialize N_CPU and threadlog. NCore shows the number of used cores.
                                            // -1 means all cores should be used. If NCore is greater than the
                                            // number of current core, N_CPU set as the current number of cores.
                                            // It should be executed as the 1st line of the code.
void free_mtutils();                        // Finalize threadlog

// threadlog
//------------------------------------------------------------------------------

#endif
