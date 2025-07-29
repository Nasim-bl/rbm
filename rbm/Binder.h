/***  Binder cumulant, Ver 0.5, Date: 17 May 2022 *****************************
 ***                                                                        ***
 ***  Copyleft (ɔ) Nasim.Bolhasani 2020-22, All lefts reserved!             ***
 ***                                                                        ***
 ******************************************************************************
 *
 * This code is under construction. It might contain some errors.
 * So you can try it at your own risk!
 */

#ifndef BINDER

#define BINDER

struct BinderCumulant {                     // Binder cumulant
  public:
      BinderCumulant();
      void sample(float x2);                // gets a new sample.
      void init();                          // initiates the variables and sets BC to zero.
      float BC(bool reset=false);           // calculates Binder cumulant. Then reset to its initial state for
                                            // a next calculation if r is true.
  private:
    int    counter;                         // shows number of samples.
    double sum2,                            // summation which is used inthe  calculation of 2ⁿᵈ
           sum4;                            // and 4ᵗʰ moments of 〈μᵢ〉.
    double bc;
};

#endif
