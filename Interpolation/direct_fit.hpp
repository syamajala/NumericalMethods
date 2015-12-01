#ifndef INTERPOLATION_DIRECT_FIT_H
#define INTERPOLATION_DIRECT_FIT_H

#include <cmath>
#include <armadillo>
#include "fit.hpp"

using namespace arma;

namespace Interpolation {
  template <class T>
    class DirectFit : public Fit<T> {
  public:
  DirectFit(const vector<T> &x, const vector<T> &f) : Fit<T>(x, f) {};

    /* given (x, f(x)) to fit around a point p, we:
     * 1. compute (n+1) nearest neighbors to p (ie, closest x values)
     * 2. build matrix (n+1)x(n+1) matrix M st f_i = a_0 + a_1*x_1 + ... + a_n+(x_i)^n
     *    for 0 <= i <= n
     * 3. solve system for coeff a_i
     * 4. P_n(x) = a_0+a_1*x+ ... + a_n*x^n
     * we return a lambda so the computed function can be compared to the actual function
     * throughout a neighborhood of the point we fit around.
     */
    vector<T> coeffs(const T point, const int deg) {
      vector<T> vM;
      vector<T> vsorted_f;

      vector<int> nnIdx = this->neighbors(point, deg);

      for(int i = 0; i < deg+1; i++) {
        vsorted_f.push_back(this->f[nnIdx[i]]);
        for(int j = 0; j < deg+1; j++) {
          T p = this->x[nnIdx[j]];
          vM.push_back(pow(p, i));
        }
      }

      Mat<T> M = conv_to<Mat<T>>::from(vM);
      M = reshape(M, deg+1, deg+1);
      Col<T> sorted_f = conv_to<Col<T>>::from(vsorted_f);
      sorted_f = solve(M, sorted_f);
      return conv_to<vector<T>>::from(sorted_f);
    }

    function<T (T)> fit(const T point, const int deg) {
      vector<T> sorted_f = coeffs(point, deg);

      function<T (T)> poly = [sorted_f](T _x) -> T {
        T s = 0;
        for(size_t i = 0; i < sorted_f.size(); i++)
          s += sorted_f[i]*pow(_x, i);
        return s;
      };

      return poly;
    };
  };
}
#endif
