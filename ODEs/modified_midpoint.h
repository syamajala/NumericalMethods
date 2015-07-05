#ifndef MODIFIED_MIDPOINT_H
#define MODIFIED_MIDPOINT_H

#include <vector>
#include "IVP.h"

using namespace std;

template <class T>
class ModifiedMidpoint : public IVP<T> {
 protected:
  T yp_nplusonehalf(int n) {
    return this->y_n[n] + (this->step_size/2.0)*this->f_n[n];
  };

  T fp_nplusonehalf(int n) {
    return this->derivative(n*this->step_size, yp_nplusonehalf(n));
  };

  T yc_nplusone(int n) {
    return this->y_n[n] + (this->step_size)*fp_nplusonehalf(n);
  };

  T y_nplusone(int n) {
    return yc_nplusone(n);
  };

 public:
 ModifiedMidpoint(T y, T f, T step_size, int steps) :
  IVP<T>(y, f, step_size, steps) {};
};

#endif
