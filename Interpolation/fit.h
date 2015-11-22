#ifndef FIT_H
#define FIT_H

#include <functional>
#include <vector>
#include <ANN/ANN.h>

using std::vector;
using std::function;

template <class T>
class Fit {
 protected:
  const vector<T> &x;
  const vector<T> &f;
 public:
 Fit(const vector<T> &x, const vector<T> &f) : x(x), f(f) {};
  virtual function<T (T)> fit(T point, int deg) = 0;

  vector<int> neighbors(const T point, const int deg) {
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

};

#endif
