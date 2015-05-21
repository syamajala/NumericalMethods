#include <cmath>
#include "newton.h"

Newton::Newton(double initial_guess, double e) : initial_guess(initial_guess), e(e) {};

double Newton::iterate() {
  double fphi_i = f(this->initial_guess);
  double dfphi_i = df(this->initial_guess);
  double phi_iplusone = this->initial_guess - (fphi_i/dfphi_i);

  while(abs(phi_iplusone - fphi_i) >= e && abs(fphi_i) >= e) {
    fphi_i = f(phi_iplusone);
    dfphi_i = df(phi_iplusone);
    phi_iplusone = phi_iplusone - (fphi_i/dfphi_i);
  }

  return phi_iplusone;
}
