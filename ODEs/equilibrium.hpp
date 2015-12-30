#ifndef ODES_EQUILIBRIUM_H
#define ODES_EQUILIBRIUM_H

#include <armadillo>
#include <vector>
#include <utility>
#include "BVP.hpp"

using namespace arma;
using std::vector;
using std::pair;

namespace ODEs {
  template <class T>
  class Equilibrium : public BVP<T> {
  public:
    Equilibrium(pair<T, T> &start_end, vector<T> &ic, T step_size, int steps) :
      BVP<T>(start_end, ic, step_size, steps) {};

    void iterate() {
      T start = this->start_end.first;
      this->x.push_back(start);
      T step_size_square = pow(this->step_size, 2);
      Mat<T> fde(this->steps-1, this->steps-1, fill::zeros);
      Col<T> r(this->steps-1, fill::zeros);

      for(int i = 1; i < this->steps-2; i++) {
        this->x.push_back(start+i*this->step_size);
        T pxi = this->P(this->x[i]);
        fde(i, i-1) = 1 - (this->step_size/2.0)*pxi;
        fde(i, i) = -2 + step_size_square*this->Q(this->x[i]);
        fde(i, i+1) = 1 + (this->step_size/2.0)*pxi;
        r(i) = step_size_square*this->F(this->x[i]);
      }

      fde(0, 0) = -2 + step_size_square*this->Q(this->x[1]);
      fde(0, 1) = 1 + (this->step_size/2.0)*this->P(this->x[1]);
      fde(0, 2) = 0;
      r(0) = -1*this->ic[0];

      this->x.push_back(this->start_end.second);

      fde(this->steps-2, this->steps-4) = 0;
      fde(this->steps-2, this->steps-3) = 1 - (this->step_size/2.0)*this->P(this->x[this->steps]);
      fde(this->steps-2, this->steps-2) = -2 + step_size_square*this->Q(this->x[this->steps]);
      r(this->steps-2) = -1*this->ic[1];

      Col<T> s = solve(fde, r);
    };

  };
}

#endif
