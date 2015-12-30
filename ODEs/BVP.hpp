#ifndef ODES_BVP_H
#define ODES_BVP_H

#include <vector>
#include <utility>
#include <boost/format.hpp>

using std::vector;
using std::pair;
using std::ostream;

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
    virtual void iterate() = 0;

    friend ostream& operator<< (ostream &os, const BVP<T> &obj) {
      for(size_t i = 0; i < obj.x.size(); i++) {
        os << boost::format("n = %=i\tx_%i = %f\tf_%i = %f\n")
          % i % i % obj.x[i]
          % i % obj.f[i];
      }
      return os;
    };
  };
}

#endif
