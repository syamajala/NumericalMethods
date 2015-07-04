#ifndef MODIFIED_EULER_H
#define MODIFIED_EULER_H

#include <vector>
#include "IVP.h"

using namespace std;

template <class T>
class ModifiedEuler : public IVP<T> {
 protected:
  T yp_nplusone(int n) {
    return this->y_n[n] + this->step_size*this->f_n[n];
  };

  T fp_nplusone(int n) {
    return this->derivative(n*this->step_size, yp_nplusone(n));
  };

  T yc_plusone(int n) {
    return this->y_n[n] + (this->step_size/2.0)*(this->f_n[n] + fp_nplusone(n));
  };

 public:
 ModifiedEuler(T y, T f, T step_size, int steps) :
  IVP<T>(step_size, steps) {
    this->y_n.push_back(y);
    this->f_n.push_back(f);
  };

  void iterate() {
    for(int n = 1; n <= this->steps; n++) {
      this->y_n.push_back(yc_plusone(n-1));
      this->f_n.push_back(this->derivative(n*this->step_size, this->y_n[n]));
    }
  };
};

#endif
