#ifndef ODES_ADAMS_MOULTON_H
#define ODES_ADAMS_MOULTON_H

#include "IVP.hpp"

namespace ODEs {
  template <class T, class S>
  class AdamsMoulton : public IVP<T, S> {
  protected:

    T yp_nplusone(int n) {
      return this->y_n[n] + (1.0/24.0)*this->step_size*(55*this->f_n[n] - 59*this->f_n[n-1] + 37*this->f_n[n-2] - 9*this->f_n[n-3]);
    };

    T fp_nplusone(int n) {
      return this->derivative(n*this->step_size, yp_nplusone(n));
    };

    T yc_nplusone(int n) {
      return this->y_n[n] + (1.0/24.0)*this->step_size*(9*fp_nplusone(n) + 19*this->f_n[n] - 5*this->f_n[n-1] + this->f_n[n-2]);
    };

    T y_nplusone(int n) {
      return yc_nplusone(n);
    };
  public:
    AdamsMoulton(IVP<T, S> &ic, S step_size, int steps) :
      IVP<T, S>(ic.y_n, ic.f_n, step_size, steps) {};

    virtual void iterate() {
      for(int n = 4; n <= this->steps; n++) {
        this->y_n.push_back(y_nplusone(n-1));
        this->f_n.push_back(this->derivative(n*this->step_size, this->y_n[n]));
      };
    }
  };
}

#endif
