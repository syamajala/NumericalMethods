#ifndef ODES_BVP_H
#define ODES_BVP_H

#include <vector>
#include <utility>

using std::vector;
using std::pair;

namespace ODEs {
  template <class T>
  class BVP {
  protected:
    pair<T, T> start_end;
    vector<T> x;
    vector<T> f;
    vector<T> ic;
    T step_size;
    int steps;
  public:
    BVP(pair<T, T> &start_end, vector<T> &ic, T step_size, int steps) :
      start_end(start_end), ic(ic), step_size(step_size), steps(steps) {};

    virtual T P(T x) = 0;
    virtual T Q(T x) = 0;
    virtual T F(T x) = 0;
  };
}

#endif
