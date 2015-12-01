#ifndef INTERPOLATION_NEWTON_H
#define INTERPOLATION_NEWTON_H

#include <iostream>
#include "binomial_coefficients.hpp"
#include "fit.hpp"

using std::cout;
using std::endl;

namespace Interpolation {
  template <class T>
    class Newton : public Fit<T> {
  protected:
    T step_size;
    vector<vector<T>> table;
    int deg;

    void build_table(const int deg) {
      if (!table.empty())
        return;

      table.push_back(this->x);
      table.push_back(this->f);

      for(int n = 2; n <= deg+1; n++) {
        vector<T> n_nodes;
        for(size_t i = 0; i < table[n-1].size() - 1; i++) {
          n_nodes.push_back(table[n-1][i+1] - table[n-1][i]);
        }
        table.push_back(n_nodes);
      }
    };

  public:
  Newton(const vector<T> &x, const vector<T> &f, T step_size) : Fit<T>(x, f), step_size(step_size)
    {};
  };

  template <class T>
    class ForwardDifference : public Newton<T> {
  public:
  ForwardDifference(const vector<T> &x, const vector<T> &f, T step_size) :
    Newton<T>(x, f, step_size) {};

    function<T (T)> fit(const T point, const int deg) {
      this->build_table(deg);

      function<T (T)> poly = [&, deg](T _x) -> T {
        vector<int> nnIdx = this->neighbors(_x, 0);
        int x0_idx = nnIdx[0];
        T s = (_x - this->x[x0_idx])/(this->step_size);
        T r = this->table[1][x0_idx];
        for(int n = 2; n <= deg+1; n++) {
          T coeff = binomial_coefficient<T>(s, n-1);
          r += (coeff*this->table[n][x0_idx]);
        }
        return r;
      };

      return poly;
    };
  };

  template <class T>
    class BackwardDifference : public Newton<T> {
  public:
  BackwardDifference(const vector<T> &x, const vector<T> &f, T step_size) :
    Newton<T>(x, f, step_size) {};

    function<T (T)> fit(const T point, const int deg) {
      this->build_table(deg);

      function<T (T)> poly = [&, deg](T _x) -> T {
        vector<int> nnIdx = this->neighbors(_x, 1);
        int x0_idx = this->x.size() - 1 - nnIdx[1];
        T s = (_x - this->x[x0_idx])/(this->step_size);
        T r = this->table[1][x0_idx];
        for(int n = 2; n <= deg+1; n++) {
          T coeff = nonstandard_binomial_coefficient<T>(s, n-1);
          int idx = this->table[n].size() - 1 - x0_idx;
          r += (coeff*this->table[n][idx]);
        }
        return r;
      };

      return poly;
    }
  };
}

#endif
