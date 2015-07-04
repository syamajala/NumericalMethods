/*
 * Solve the initial value ODE:
 * y' = f(t, y), y(t_0) = y_0
 * using the finite difference equation:
 * y_(n+1) = y_n + del_t*f_n
 */

#ifndef EXPLICIT_EULER_H
#define EXPLICIT_EULER_H

#include <vector>
#include "IVP.h"

using namespace std;

template <class T>
class ExplicitEuler : public IVP<T> {
 public:
 ExplicitEuler(T y, T f, T step_size, int steps) :
  IVP<T>(step_size, steps) {
    this->y_n.push_back(y);
    this->f_n.push_back(f);
  };

  T y_nplusone(int n) {
    return this->y_n[n] + this->step_size*this->f_n[n];
  };

  void iterate()  {
    for(int n = 1; n <= this->steps; n++) {
      this->y_n.push_back(y_nplusone(n-1));
      this->f_n.push_back(this->derivative(n*this->step_size, this->y_n[n]));
    }
  };
};
 #endif
