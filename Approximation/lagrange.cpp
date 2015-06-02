#include "lagrange.h"

function<float (float)> Lagrange::fit(float point, int deg) {
  vector<int> nnIdx = neighbors(point, deg);
  
  function<float (float)> poly = [&, nnIdx, deg](float _x) -> float {
    float s = 0;
    for(int i = 0; i < deg+1; i++) {
      float num = 1;
      float denom = 1;
      for(int j = 0; j < deg+1; j++) {
	if(j != i) {
	  num *= (_x - x[nnIdx[j]]);
	  denom *= x[nnIdx[i]] - x[nnIdx[j]];
	}
      }
      s += (num/denom)*f[nnIdx[i]];
    }
    return s;
  };

  return poly;
}
