#ifndef DIFFERENTIATION_DIRECT_FIT_H
#define DIFFERENTIATION_DIRECT_FIT_H

#include <cmath>
#include <vector>
#include <functional>

using std::vector;
using std::function;

namespace Differentiation {
  template <class T>
    class DirectFit {
  private:
    vector<T> coeffs;
  public:
  DirectFit(const vector<T> coeffs) : coeffs(coeffs) {};

    vector<T> compute_coeffs() {
      vector<T> new_coeffs;
      for(size_t i = 1; i < coeffs.size(); i++) {
        new_coeffs.push_back(i*coeffs[i]);
      }
      return new_coeffs;
    }

    function<T (T)> differentiate() {
      vector<T> new_coeffs = this->compute_coeffs();

      function<T (T)> poly = [new_coeffs](T _x) -> T {
        T s = 0;
        for(size_t i = 0; i < new_coeffs.size(); i++) {
          s += new_coeffs[i]*pow(_x, i);
        }
        return s;
      };
      return poly;
    }

  };
}

#endif
