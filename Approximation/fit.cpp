#include <ANN/ANN.h>
#include "fit.h"

vector<int> Fit::neighbors(const float point, const int deg) {
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

  vector<int> idx(nnIdx, nnIdx+deg+1);
  
  delete [] nnIdx;
  delete [] dists;
  delete kdTree;
  annDeallocPt(queryPt);
  annDeallocPts(dataPts);
  annClose();

  return idx;
}
