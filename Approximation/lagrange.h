#include "fit.h"

using namespace std;

template <class T>
class Lagrange : public Fit<T> {
 public:
 Lagrange(const vector<T> &x, const vector<T> &f) : Fit<T>(x, f) {};
  function<T (T)> fit(const T point, const int deg) {
    vector<int> nnIdx = this->neighbors(point, deg);
  
    function<T (T)> poly = [&, nnIdx, deg](T _x) -> T {
      T s = 0;
      for(int i = 0; i < deg+1; i++) {
	T num = 1;
	T denom = 1;
	for(int j = 0; j < deg+1; j++) {
	  if(j != i) {
	    num *= (_x - this->x[nnIdx[j]]);
	    denom *= this->x[nnIdx[i]] - this->x[nnIdx[j]];
	  }
	}
	s += (num/denom)*this->f[nnIdx[i]];
      }
      return s;
    };

    return poly;
  };
};
