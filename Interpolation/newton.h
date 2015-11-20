#ifndef NEWTON_H
#define NEWTON_H

#include "fit.h"
#include "difference.h"

using namespace std;

template <class T>
class ForwardDifference : public Difference<T> {
 protected:
  T step_size;

 public:
 ForwardDifference(const vector<T> &x, const vector<T> &f, T step_size) :
  Difference<T>(x, f), step_size(step_size) {};

  function<T (T)> fit(const T point, const int deg) {
    this->build_table(point, deg);

    function<T (T)> poly = [this](T _x) -> T {
      return _x;
    };

    return poly;
  };

};

#endif
