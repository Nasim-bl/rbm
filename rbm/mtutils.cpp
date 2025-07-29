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

/* OpenMP Note:
  Code should be compiled with the -fopenmp switch of gcc.
*/

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#ifdef _OPENMP // Use omp.h if -fopenmp is used in g++
  #include <omp.h>
#endif
#include "mtutils.h"

using namespace std;

// Thread Variables
int N_CPU = 1;                              // Shows number of CPU

//------------------------------------------------------------------------------
// threadlog

// threadlog is a separate log file for each thread
ofstream threadlog;
#pragma omp threadprivate(threadlog)        // This line makes threadlog threadsafe variable;
                                            //Each thread has its own copy of the variable.

// threadlog
//------------------------------------------------------------------------------

// Initialize N_CPU and threadlog. NCore shows the number of used cores. -1 means all cores
// should be used. If NCore is greater than the number of current cores, N_CPUis  set as the
// current number of cores.

void init_mtutils(int NCore) {

    #ifdef _OPENMP
        int N = omp_get_num_procs();        // The current number of CPU cores
        if ((NCore == -1) || (NCore > N))
            N_CPU = N;                      // Use all of CPU cores
        else
          N_CPU = NCore;                    // limit number of used cores to NCore

        omp_set_num_threads(N_CPU);

        #pragma omp parallel num_threads(N_CPU)
        {
            int id = omp_get_thread_num();
            char buf[40];
            sprintf(buf, "thread%d.log", id);
            threadlog.open(buf);
        }
    #else
        N_CPU = 1;
        threadlog.open("thread0.log");
    #endif
}

// Finalize threadlog
void free_mtutils() {
    #ifdef _OPENMP
        #pragma omp parallel num_threads(N_CPU)
        {
            threadlog.close();
        }
    #else
        threadlog.close();
    #endif
}

