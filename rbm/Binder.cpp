/***  Binder cumulant, Ver 0.5, Date: 22 May 2022******************************
 ***                                                                        ***
 ***  Copyleft (ɔ) Nasim. Bolhasan 2020-22, All lefts reserved!             ***
 ***                                                                        ***
 ******************************************************************************
 *
 * This code is under construction. It might contain some errors.
 * So you can try it at your own risk!
 */

#include <cstdlib>
#include <math.h>
#include "Binder.h"
#include "utils.h"

using namespace std;

BinderCumulant::BinderCumulant() {
    init();
}

void BinderCumulant::sample(float x2) {     // gets a new sample.
    sum2 += x2;
    sum4 += sqr(x2);
    counter++;
}

void BinderCumulant::init() {              // initiates the variables and sets BC to zero.
    counter = 0;
    sum2 = sum4 = 0;
    bc = 0;
}

// calculates Binder cumulant. Then reset to its initial state for next calculation if r is true.
float BinderCumulant::BC(bool reset) {
    if (counter > 0) {
        double M2 = sum2 / counter,         // 2ⁿᵈ and  and
               M4 = sum4 / counter;         // 4ᵗʰ moments of 〈μᵢ〉 are calculated.
        bc = 1. - 3. * M4 / (5. * sqr(M2)); // Binder cumulant
    } else
        bc = 0;

    if (reset) {
        counter = 0;
        sum2 = sum4 = 0;
    }

    return bc;
}
