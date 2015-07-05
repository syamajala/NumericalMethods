// Fourth order Runge Kutta method

#ifndef RUNGE_KUTTA_H
#define RUNGE_KUTTA_H

#include <vector>
#include "IVP.h"

using namespace std;

template <class T>
class RungeKutta : public IVP<T> {
 protected:
  T del_y1(int n) {
    return this->step_size*this->derivative(n*this->step_size, this->y_n[n]);
  };

  T del_y2(int n) {
    return this->step_size*this->derivative(n*this->step_size + this->step_size/2.0,
                                      this->y_n[n] + del_y1(n)/2.0);
  };

  T del_y3(int n) {
    return this->step_size*this->derivative(n*this->step_size + this->step_size/2.0,
                                      this->y_n[n] + del_y2(n)/2.0);
  };

  T del_y4(int n) {
    return this->step_size*this->derivative(n*this->step_size + this->step_size,
                                      this->y_n[n] + del_y3(n));
  };

  T y_nplusone(int n) {
    return this->y_n[n] + (1.0/6.0)*(del_y1(n) + 2*del_y2(n) + 2*del_y3(n)
                                           + del_y4(n));
  };
 public:
 RungeKutta(T y, T f, T step_size, int steps) :
  IVP<T>(y, f, step_size, steps) {};
};
#endif
