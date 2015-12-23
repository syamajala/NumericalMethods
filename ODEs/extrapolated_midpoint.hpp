#ifndef ODES_EXTRAPOLATED_MIDPOINT_H
#define ODES_EXTRAPOLATED_MIDPOINT_H

#include <vector>
#include "IVP.hpp"

namespace ODEs {
  template <class T, class S>
  class ExtrapolatedMidpoint : public IVP<T, S> {
  protected:
    T M;
    T h;

    T z_i(int i, int n) {
      switch (i) {
      case 0:
        return this->y_n[n];
      case 1: {
        T z_0 = z_i(0, n);
        return z_0 + h*this->derivative(n*this->step_size, z_0);
      }
      default:
        return z_i(i-2, n) + 2*h*this->derivative((i-1)*h + n*this->step_size, z_i(i-1, n));
      }
    };

  public:
  ExtrapolatedMidpoint(T y, T f, S step_size, int steps, int M) :
    IVP<T, S>(y, f, step_size, steps), M(M), h(step_size/M) {};

    T y_nplusone(int n) {
      T z_M = z_i(M, n);
      return 0.5*(z_i(M-1, n) + z_M + h*this->derivative(this->step_size + n*this->step_size,
                                                         z_M));
    };
  };
}
#endif
