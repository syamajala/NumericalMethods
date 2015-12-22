#ifndef ODES_IMPLICIT_EULER_H
#define ODES_IMPLICIT_EULER_H

#include <vector>
#include "NonlinearSystems/newton.hpp"
#include "IVP.hpp"

namespace ODEs {
  template <class T>
  class ImplicitEuler : public NonlinearSystems::Newton<T>, public IVP<T> {
  protected:
    int cur_step = 1;

    T y_nplusone(int n) {
      this->initial_guess = this->y_n[n];
      T y = NonlinearSystems::Newton<T>::iterate();
      return y;
    }

    T f(int n, T x) {
      return x - this->y_n[n] - this->step_size*this->derivative(n*this->step_size, x);
    };

    T df(int n, T x) {
      return 1 - this->step_size*this->dderivative(n*this->step_size, x);
    };

  public:
    ImplicitEuler(T y, T f, T step_size, int steps) :
      NonlinearSystems::Newton<T>(y, 0.0001), IVP<T>(y, f, step_size, steps)  {};

    T f(T x) {
      return this->f(this->cur_step-1, x);
    };

    T df(T x) {
      return this->df(this->cur_step-1, x);
    };

    virtual T dderivative(T t_n, T y_n) = 0;

    virtual void iterate() {
      for(; this->cur_step <= this->steps; this->cur_step++) {
        this->y_n.push_back(y_nplusone(cur_step-1));
        this->f_n.push_back(this->derivative(cur_step*this->step_size, this->y_n[cur_step]));
      }
    };
  };
}

#endif
