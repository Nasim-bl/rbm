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

#ifndef UTILS_H

#define UTILS_H

//#define DEBUG_MODE                        // Activate the debug mode
//#define NO_WAIT                           // Deactivate wait() at the end of code; this means the
                                            //‎ The application does not wait at the end of execution in wait().
                                            // However, this definition must insert in the main code before
                                            //‎ including the utils.h header.
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#if defined(_WIN32) || defined(_WIN64)
  #include <conio.h>
#endif
#define _USE_MATH_DEFINES                   // Force the M_PI library to define the math.h
#include <math.h>
#include <limits>
#include <cstring>

//------------------------------------------------------------------------------
// math routine
const long double pi = 	3.14159265358979323846;// Define pi with the machine precision based on its definition in math.h

template <typename Number>                  // Type of any number
inline Number sqr(Number x) { return x*x; }
template <typename Number>                  // Type of any number
inline Number ipow(Number base, int exp) {  // Optimized power function with an integer exponent
    if (exp >= 0) {
        Number result = 1.0;
        while (exp) {
            if (exp & 1)
                result *= base;
            exp >>= 1;
            base *= base;
        }
        return result;
    } else
        return 1.0 / ipow(base, -exp);
}
// math routine
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Filename manipulation
// Check if a file exist
inline bool IsFileExist(const char* filename) {
    std::ifstream f(filename);
    return f.good();
}

// Here, we must reference to:
// https://stackoverflow.com/questions/6417817/easy-way-to-remove-extension-from-a-filename
// for the following function.
// Quote: "More complex, but with respect to special cases (for example: "foo.bar/baz",
// "c:foo.bar", works for Windows too)"
std::string remove_extension(const std::string& path);
// Filename manipulation
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Backward compatibility section
// C++11 feature such as nullptr was not supported in older compilers (previous than gcc 4.6)
// for gcc 4.6 nullptr are experimentally supported and activate when using -std=c1x switch with g++ compiler,
// for gcc 4.7 nullptr are supported when using -std=c11 switch with g++ compiler,
// and in the recent gcc compilers this definition is supported by default
#if (defined(__GNUC__) && __GNUC__ > 4) || (defined(__GNUC__) && __GNUC__ == 4 && __GNUC_MINOR__ >= 6) || \
    (defined(_MSC_VER) && _MSC_VER >= 1900) || defined(__cpp_lib_is_null_pointer)
    // C++11 features such as nullptr is supported
#else
    // C++11 features such as nullptr is not supported
    #define nullptr NULL
#endif
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// wait() pauses the consul(terminal) till the time when any key is pressed
// This routine is independent of OS
#if defined(__linux__) || defined(__APPLE__)
  char getch(void);
  char getche(void);
#endif
#ifdef NO_WAIT
  inline void wait() { std::cout << "NO_WAIT definition disable wait() routine" << std::endl; }
#else
  inline void wait() {
      void __wait();
      __wait();
  }
#endif
// wait()
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// DEBUG_MODE
#ifdef DEBUG_MODE
  #define DEBUG(X) { X; }
  #define NODEBUG(X) ; /* Nothing */
#else
  #define DEBUG(X) ; /* Nothing */
  #define NODEBUG(X) { X; }
#endif
// DEBUG_MODE
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// logger and lout
/* lout is similar to clog. But its outputs are simultaneously exported to "log.txt".
 * endl can be used as in a cout or any other text stream.
 * To on/off streaming to the terminal use eoff/eon, e.g.
 *   lout << "terminal & log file " << eoff << " only log file " << eon << " terminal & log file " << endl;
 * Progressive task are supported by prog and endp. This compatibility work as progress bar in terminal. The
 * text between prog and endp rewrite in a same line of the terminal and the log file, e.g.
 *   lout << prog << "t: " << time << endp;
 * endp is used here instead of endl to mark end of progressive text. */
class logger {
    private:
        std::ofstream logfile;              // Log file
        bool em;                            // State of the echo mode.
        int progm;                          // State of the progress mode
                                            // 0: Disable
                                            // 1: Inside the presentation of progressive task bar text
                                            // 2: At the end of progressive task bar text (endp)
        std::clock_t start_time;            // Internal variable used by the timmer
        int lfp;                            // Store the position of prog at the log file
    public:
        logger(const char* file);
        ~logger();
        std::ofstream& noecho(void);
        logger& echo(bool e);
        logger& prog(void) {
            if (progm == 0) {
                //std::clog << std::endl;
                *this << std::endl;
                lfp = logfile.tellp();
            }
            progm = 1;
            NODEBUG(std::clog << "\r");
            NODEBUG(logfile.seekp(lfp));
            return *this;
        }
        logger& endp(void) {
            if (progm == 1) {
                progm = 2;
                DEBUG(*this << std::endl);
                //NODEBUG(logfile << std::endl);
            }
            return *this;
        }
        logger& reset(long int s);     // See the file pointer at the beginning of the logfile if its size exceeds than s.
                                       // So, the logfile is filled with periodic condition and part of previous content available
                                       // at the end of file.
                                       // Example: lout.reset(65536);
        logger& start();               // Start the timer
        logger& stop();                // Stop timer and print duration time, e.g.
                                       //   lout.start();
                                       //   /* Your algorithm here */
                                       //   lout.stop();

        template <class T>
        logger& operator<<(const T& out) {
            if (progm == 2) {
              NODEBUG(std::clog << std::endl);
              progm = 0;
            }
            if (em) std::clog << out;
            logfile << out;

            return *this;
        }

        logger& operator<<( std::ostream& (*pf)( std::ostream& ) ) {
            //  For manipulators...
            if (em) std::clog << (*pf);
            logfile << (*pf);

            return *this;
        }

        logger& operator<<( std::basic_ios<char>& (*pf)( std::basic_ios<char>& ) ) {
            //  For manipulators...
            if (em) std::clog << (*pf);
            logfile << (*pf);

            return *this;
        }

        logger& operator<<( logger& (*pf)( logger& ) ) {
            //  For new manipulators: eoff, eon, prog, endp
            (*pf)(*this);

            return *this;
        }
};

extern logger lout;                         // Define "log.txt" as a log file.

inline logger& eoff(logger& is) {
    is.echo(false);
    return is;
}

inline logger& eon(logger& is) {
    is.echo(true);
    return is;
}

inline logger& prog(logger& is) {
    return is.prog();
}

inline logger& endp(logger& is) {
    return is.endp();
}

// logger and lout
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Plot routines
/* Using gnuplot to plot (x,y) data point
   if x is omitted or NULL, the zero based sequential data is used instead of it for x axis.
   N shows the number of data points in x and y array.
   xlog and xlog set the x and y axis with the logarithmic scale.
   tempfilename shows temp file name. If this argument omitted the default file name equal to "temp.txt" is used.
*/
template <typename Number1, typename Number2>
inline void plot(Number1* x, Number2* y, int N, bool xlog=false, bool ylog=false, const char* tempfilename=nullptr) {
    using namespace std;
    // define internal utility function in utils.cpp
    void GNUPlotHeader(ofstream& temp, bool xlog=false, bool ylog=false);
    void GNUPlotFooter(ofstream& temp);
    void GNUPlot(const char* tempfilename);

    char deffilename[] = "temp.txt";        // default temporary gnuplot script file name
    if (tempfilename == 0)
        tempfilename = deffilename;

    ofstream temp(tempfilename, ios::out | ios::trunc);

    GNUPlotHeader(temp, xlog, ylog);

    if (x == 0)                             // If x is NULL use sequential data
        for(int i=0; i<N; i++)
            temp << i << '\t' << y[i] << endl;
    else                                    // else
        for(int i=0; i<N; i++)
            temp << x[i] << '\t' << y[i] << endl;

    GNUPlotFooter(temp);

    temp.close();

    GNUPlot(tempfilename);
}
template <typename Number>
inline void plot(Number* y, int N, bool xlog=false, bool ylog=false, const char* tempfilename=nullptr) {
    plot<int, Number>(NULL, y, N, xlog, ylog, tempfilename);
}

// Plot routines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// These are here for test
/*template <typename Number1, typename Number2>
void testprint(Number1 x, Number2 y);*/

//------------------------------------------------------------------------------

#endif
