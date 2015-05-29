#include <iostream>
#include <cmath>
#include <ANN/ANN.h>
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

DirectFit::DirectFit(vector<float> &x, vector<float> &f) : x(x), f(f) {}

void DirectFit::build_system(float point, int deg, vector<float> &M,
			     vector<float> &sorted_f) {
  double eps = 0;
  int maxPts = x.size();
  int dim = 1;
  ANNpointArray dataPts = annAllocPts(maxPts, dim);
  ANNpoint queryPt = annAllocPt(dim);

  for(int i = 0; i < maxPts; i++)
    dataPts[i][0] = x[i];

  queryPt[0] = point;
  
  ANNidxArray nnIdx = new ANNidx[deg+1];
  ANNkd_tree *kdTree = new ANNkd_tree(dataPts, maxPts, dim);
  ANNdistArray dists = new ANNdist[deg+1];
  kdTree->annkSearch(queryPt, deg+1, nnIdx, dists, eps);

  for(int i = 0; i < deg+1; i++) {
    sorted_f.push_back(f[nnIdx[i]]);
    for(int j = 0; j < deg+1; j++) {
      float p = x[nnIdx[j]];
      M.push_back(pow(p, i));
    }
  }

  delete [] nnIdx;
  delete [] dists;
  delete kdTree;
  annDeallocPt(queryPt);
  annDeallocPts(dataPts);
  annClose();
}

function<float (float)> DirectFit::fit(float point, int deg) {
  vector<float> M;
  vector<float> sorted_f;
  build_system(point, deg, M, sorted_f);

  char TRANS = 'N';
  int NRHS = 1;
  int IPIV[deg+1];

  LAPACKE_sgetrf(LAPACK_COL_MAJOR, deg+1, deg+1, &(M[0]), deg+1, &IPIV[0]);

  LAPACKE_sgetrs(LAPACK_COL_MAJOR, TRANS, deg+1, NRHS, &(M[0]), deg+1,
		 &(IPIV[0]), &(sorted_f[0]), deg+1);
  
  function<float (float)> poly = [sorted_f](float y) -> float {
    float s = 0;
    for(size_t i = 0; i < sorted_f.size(); i++)
      s += sorted_f[i]*pow(y, i);
    return s;
  };

  return poly;
}
