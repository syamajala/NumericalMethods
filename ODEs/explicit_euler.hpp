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
  template <class T, class S>
  class ExplicitEuler : public IVP<T, S> {
  protected:
    T y_nplusone(int n) {
      return this->y_n[n] + this->step_size*this->f_n[n];
    };

  public:
    ExplicitEuler(T y, T f, S step_size, int steps) :
      IVP<T, S>(y, f, step_size, steps) {};
  };
}
#endif
