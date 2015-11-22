#ifndef MODIFIED_EULER_H
#define MODIFIED_EULER_H

#include <vector>
#include "IVP.h"

template <class T>
class ModifiedEuler : public IVP<T> {
 protected:
  T yp_nplusone(int n) {
    return this->y_n[n] + this->step_size*this->f_n[n];
  };

  T fp_nplusone(int n) {
    return this->derivative(n*this->step_size, yp_nplusone(n));
  };

  T yc_nplusone(int n) {
    return this->y_n[n] + (this->step_size/2.0)*(this->f_n[n] + fp_nplusone(n));
  };

  T y_nplusone(int n) {
    return yc_nplusone(n);
  };

 public:
 ModifiedEuler(T y, T f, T step_size, int steps) :
  IVP<T>(y, f, step_size, steps) {};
};

#endif
