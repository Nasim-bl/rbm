/******************************************************************************/
/*** General Utility                                                        ***/
/*** Ver 1.62                                                               ***/
/*** Date: 14010226                                                         ***/
/*** Copyleft (c) 2013-2022 by O. Farzadian, M. Zarepour, A. Alipour,       ***/
/*** L. Elyasizad, M. Delbari, M. Mortazavi Rad, K. Ahmadi, F. Bolhasani,   ***/
/*** and M. D. Niry. All lefts reserved!                                    ***/
/*** Licensed under The GNU General Public License v3.0                     ***/
/*** Code implemented in GNU C++ compiler (v. 4.6.3) in 64-bit UBUNTU 12.04 ***/
/*** Run under an Intel® Core™ i3-2330M CPU @ 2.20GHz × 4 machine with 2 GB ***/
/*** RAM.                                                                   ***/
/******************************************************************************/

// Ver 1.55
// Date: 13951008
// plot() routines was added to version 1.45 by L. Elyasizad in 2016

// Ver 1.56
// Date 13980230
// Backward compatibility was added to version 1.55 by K. Ahmadi in 2019
// C++11 feature such as nullptr was not supported in older compilers (previous than gcc 4.6)
// for gcc 4.6 nullptr are experimentally supported and activate when using -std=c1x switch with g++ compiler,
// for gcc 4.7 nullptr are supported when using -std=c11 switch with g++ compiler,
// and in the recent gcc compilers this definition is supported by default

// Ver 1.57
// Date 13980304
// The function reset() was added to logger by K. Ahmadi in 2019.
// By this capability, the size of log file can be checked and controlled.

// Ver 1.58
// Date 13980317
// The functions start() and stop() were added to logger by M. D. Niry in 2019
// These two functions add an internal timer to logger.
// prog and endp are updated to support the progressive log in the log file.
// This new feature decrease the log file size.

// Ver 1.60
// Date 13990621
// The function remove_extension() and IsFileExist() were added by M. D. Niry in 2019.

// Ver 1.61
// Date 14000324
// The bug in start() and stop() functions are fixed.

// Ver 1.62
// Date 14010226
// The bug in start() and stop() functions are fixed.

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h> // or cmath
#include <omp.h>

//------------------------------------------------------------------------------
// wait()
#if defined(__linux__) || defined(__APPLE__)
  #include <termios.h>
#elif defined(_WIN32) || defined(_WIN64)
#else
  #error OS not supported
#endif
// wait()
//------------------------------------------------------------------------------
#include "utils.h"

using namespace std;


//------------------------------------------------------------------------------
// Filename manipulation
// here, we must reference to:
// https://stackoverflow.com/questions/6417817/easy-way-to-remove-extension-from-a-filename
// for the following function.
// Quote: "More complex, but with respect to special cases (for example: "foo.bar/baz", "c:foo.bar",
// works for Windows too)"
std::string remove_extension(const std::string& path) {
  if (path == "." || path == "..")
    return path;

  size_t pos = path.find_last_of("\\/.");
  if (pos != std::string::npos && path[pos] == '.')
    return path.substr(0, pos);

  return path;
}
// Filename manipulation
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// wait()
#if defined(__linux__) || defined(__APPLE__)
  // Activate the new options of consul and save the current state
  void InitTerm(bool echo, struct termios& oldt) {
    tcgetattr(0, &oldt);                    // Get old state of consul
    struct termios newt = oldt;             // Initial newt for the new state of consul
    newt.c_lflag &= ~ICANON;                // Disable I/O buffer
    newt.c_lflag &= echo ? ECHO : ~ECHO;    // Set the echo mode
    tcsetattr(0, TCSANOW, &newt);           // Set the new state of consul defined in the newt
  }

  // Reset consul to its old state
  void RestoreTerm(struct termios& oldt) {
    tcsetattr(0, TCSANOW, &oldt);
  }

  // Read 1 character from consul (echo defines echo mode)
  char __getch(bool echo) {
    struct termios oldt;
    InitTerm(echo, oldt);
    char ch = getchar();
    RestoreTerm(oldt);
    return ch;
  }

  // Read 1 character from consul without echo
  char getch(void) {
    return __getch(false);
  }

  // Read 1 character  from consul with echo
  char getche(void) {
    return __getch(true);
  }

  // pause consul (terminal) till pressing any key
  void __wait() {
      cout << "\nPress any key to continue ...";
      getch();
      cout << endl;
  }
#elif defined(_WIN32) || defined(_WIN64)
  // pause consul (terminal) till pressing any key
  void __wait() {
      cout << endl;
      system("pause");
  }
#else
  void __wait() {
      cerr <<  "The wait() routine not supported in current OS" << endl;
  }
#endif
// wait()
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// logger and lout
logger lout("log.txt");                     // Defined the log file as "log.txt".

logger::logger(const char* file) {
    em = true;
    progm = 0;
    logfile.open(file);

    if (!(logfile.is_open())) {
        cerr << "[]: Couldn't open the file \"" << file << "\" for logging.\n";
        this->~logger();                    // If the log file is opened previously this class is destructed.
    }
}

logger::~logger() {
    if (logfile.is_open())
        logfile.close();
}

// Export log to the log file only.
ofstream& logger::noecho(void) {
    return logfile;
}

// On/Off the outputs to the consul.
logger& logger::echo(bool e) {
    em = e;
    return *this;
}

// Set the file pointer at the beginning of the log file if its size exceeds than s.
// So, the log file is filled with the periodic condition and part of previous content available
// at the end of the log file.
// Example: lout.reset(65536);
logger& logger::reset(long int s) {
    if (logfile.tellp() > s) {
        logfile.seekp(0);
        logfile << "log file is cleared!" << endl;
    }
    return *this;
}

// Start and stop the internal timer and print duration time, e.g.
//   lout.start();
//   /* Your algorithm here */
//   lout.stop();
logger& logger::start() {                   // Start the timer
    #ifdef _OPENMP                          // clock() measures the total time going on all cores
        start_time = omp_get_wtime();
    #else                                   // while omp_get_wtime() measure the real time could be measure by a stopwatch.
        start_time = clock();
    #endif
    return *this;
}
logger& logger::stop() {                    // Stop the timer and print the duration time
    #ifdef _OPENMP
        double duration = omp_get_wtime() - start_time;
    #else
        double duration = ( clock() - start_time ) / (double) CLOCKS_PER_SEC;
    #endif

    lout << "duration: " << setprecision(2) << fixed << duration << " sec" << endl
         << resetiosflags(std::ios_base::floatfield | std::ios_base::showpoint)
         << setprecision(-1);               // resets the stream format
    return *this;
}

// logger and lout
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Plot routines
/* Using gnuplot to plot (x,y) data points.
   utility function creates the header of temporary file used in plot() routines.
   The xlog and ylog set the x and y-axis with the logarithmic scale.
   The tempfilename shows the temporary file name. If this argument omitted the default file name equal to "temp.txt" is used.
*/
void GNUPlotHeader(ofstream& temp, bool xlog=false, bool ylog=false) {
    temp << "set ylabel \"y\"\n"
         << "set xlabel \"x\"\n"
         << "set autoscale" << endl;

    if (xlog) temp << "set logscale x" << endl;

    if (ylog) temp << "set logscale y" << endl;

    temp << "plot '-' using 1:2 title \"My Plot\" with lp" << endl;
}
void GNUPlotFooter(ofstream& temp) {
    temp << "EOF\n"
         << "pause -1 \"Hit any key to continue\"" << endl;
}
void GNUPlot(const char* tempfilename) {
    char cmd[256] = "gnuplot ";             // gnuplot command sting
    strcat (cmd, tempfilename);
    lout << "system(\"" << cmd << "\")" << endl;
    int Ret = system(cmd);
    if (Ret != 0)
      lout << "The gnuplot is failed and the returned error code is " << Ret << "." << endl;
    else
      lout << endl;
}

// Plot routines
//------------------------------------------------------------------------------

// These are here for test
/*template <typename Number1, typename Number2>
void testprint(Number1 x, Number2 y) {
    lout << "test print template: " << x << '\t' << y << endl;
}

template void testprint<int, int>(int, int);
template void testprint<float, int>(float, int);
template void testprint<int, double>(int, double);
template void testprint<double, double>(double, double);
*/
//------------------------------------------------------------------------------
