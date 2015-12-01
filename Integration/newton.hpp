#ifndef INTEGRATION_NEWTON_H
#define INTEGRATION_NEWTON_H

#include <vector>
#include "../Interpolation/newton.hpp"

using std::vector;

namespace Integration {
  template <class T>
    class Newton : public Interpolation::ForwardDifference<T> {

  public:
  Newton(Interpolation::ForwardDifference<T> &poly) : Interpolation::ForwardDifference<T>(poly) {};
    virtual T integrate(T l, T u) = 0;
  };

  template <class T>
    class Trapezoid : public Newton<T> {
  public:
  Trapezoid(Interpolation::ForwardDifference<T> &poly) : Newton<T>(poly) {};

    T integrate(T l, T u) {
      T I = 0;

      for(size_t i = 0; i < this->table[2].size(); i++) {
        I += (this->table[1][i] + 0.5*this->table[2][i]);
      }

      I *= this->step_size;

      return I;
    }
  };

  template <class T>
    class Simpson13 : public Newton<T> {
  public:
  Simpson13(Interpolation::ForwardDifference<T> &poly) : Newton<T>(poly) {};

    T integrate(T l, T u) {
      T I = 0;

      for(size_t i = 0; i < this->table[3].size(); i++) {
        I += ((2*this->table[1][i]) + (2*this->table[2][i]) + (1.0/3.0*this->table[3][i]));
      }

      I *= this->step_size;

      return I;
    }
  };
}

#endif
