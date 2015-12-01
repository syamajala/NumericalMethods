#ifndef INTEGRATION_DIRECT_FIT
#define INTEGRATION_DIRECT_FIT

#include <vector>

using std::vector;

namespace Integration {
  template <class T>
    class DirectFit {
  private:
    vector<T> coeffs;
  public:
  DirectFit(vector<T> coeffs) : coeffs(coeffs) {};

    T integrate(T l, T u) {
      vector<T> new_coeffs;
      for(size_t n = 1; n <= coeffs.size(); n++) {
        new_coeffs.push_back(coeffs[n-1]*1.0/n);
      }

      function<T (T)> poly = [new_coeffs](T _x) -> T {
        T s = 0;
        for(size_t n = 0; n < new_coeffs.size(); n++) {
          s += new_coeffs[n]*pow(_x, n+1);
        }
        return s;
      };

      return poly(u) - poly(l);
    }
  };

}

#endif
