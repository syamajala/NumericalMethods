#include <iostream>
#include <cmath>

#include <cblas.h>
#include <lapacke.h>
#include "direct_fit.h"

using namespace std;

/* given (x, f(x)) to fit around a point p, we:
 * 1. compute (n+1) nearest neighbors to p (ie, closest x values)
 * 2. build matrix (n+1)x(n+1) matrix M st f_i = a_0 + a_1*x_1 + ... + a_n+(x_i)^n
 *    for 0 <= i <= n
 * 3. solve system for coeff a_i
 * 4. P_n(x) = a_0+a_1*x+ ... + a_n*x^n
 * we return a lambda so the computed function can be compared to the actual function
 * throughout a neighborhood of the point we fit around.
 */

function<float (float)> DirectFit::fit(const float point, const int deg) {
  vector<float> M;
  vector<float> sorted_f;

  vector<int> nnIdx = neighbors(point, deg);
  
  for(int i = 0; i < deg+1; i++) {
    sorted_f.push_back(f[nnIdx[i]]);
    for(int j = 0; j < deg+1; j++) {
      float p = x[nnIdx[j]];
      M.push_back(pow(p, i));
    }
  }

  char TRANS = 'N';
  int NRHS = 1;
  int IPIV[deg+1];

  LAPACKE_sgetrf(LAPACK_COL_MAJOR, deg+1, deg+1, &(M[0]), deg+1, &IPIV[0]);

  LAPACKE_sgetrs(LAPACK_COL_MAJOR, TRANS, deg+1, NRHS, &(M[0]), deg+1,
		 &(IPIV[0]), &(sorted_f[0]), deg+1);
  
  function<float (float)> poly = [sorted_f](float _x) -> float {
    float s = 0;
    for(size_t i = 0; i < sorted_f.size(); i++)
      s += sorted_f[i]*pow(_x, i);
    return s;
  };

  return poly;
}
