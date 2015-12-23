/*
 * Solve the initial value ODE:
 * y' = f(t, y), y(t_0) = y_0
 * using the finite difference equation:
 * y_(n+1) = y_n + del_t*f_n
 */

#ifndef ODES_EXPLICIT_EULER_H
#define ODES_EXPLICIT_EULER_H

#include <vector>
#include "IVP.hpp"

namespace ODEs {
  template <class T>
  class ExplicitEuler : public IVP<T> {
  protected:
    T y_nplusone(int n) {
      return this->y_n[n] + this->step_size*this->f_n[n];
    };

  public:
    ExplicitEuler(T y, T f, T step_size, int steps) :
      IVP<T>(y, f, step_size, steps) {};
  };

  template <class T>
  class ExplicitEulerSystem : public IVPSystem<T> {
  protected:
    valarray<T> y_nplusone(int n) {
      return this->y_n[n] + this->step_size*this->f_n[n];
    };

  public:
    ExplicitEulerSystem(valarray<T> y, valarray<T> f, T step_size, int steps) :
      IVPSystem<T>(y, f, step_size, steps) {};
  };
}
#endif
