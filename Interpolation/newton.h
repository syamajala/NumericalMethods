#ifndef NEWTON_H
#define NEWTON_H

#include "fit.h"
#include "difference.h"

template <class T>
class Newton : public Fit<T>, Difference<T> {
 protected:
  T step_size;
  void build_table(const T point, const int deg) {
    vector<int> nnIdx = this->neighbors(point, deg+1);
    vector<T> sx;

    // n = 0
    vector<T> zero_nodes;
    for(auto i : nnIdx) {
      sx.push_back(this->x[i]);
      zero_nodes.push_back(this->f[i]);
    }
    this->table.push_back(zero_nodes);

    for(int n = 1; n < deg+1; n++) {
      vector<T> n_nodes;
      for(size_t i = 0; i < this->table[n-1].size() - 1; i++) {
	n_nodes.push_back(this->table[n-1][i+1] - this->table[n-1][i]);
	cout << n_nodes.back() << endl;
      }
      this->table.push_back(n_nodes);
    }
  };

 public:
 Newton(const vector<T> &x, const vector<T> &f, T step_size) : Fit<T>(x, f),
    step_size(step_size) {};
};

template <class T>
class ForwardDifference : public Newton<T> {
 public:
 ForwardDifference(const vector<T> &x, const vector<T> &f, T step_size) :
  Newton<T>(x, f, step_size) {};

  function<T (T)> fit(const T point, const int deg) {
    Newton<T>::build_table(point, deg);
    function<T (T)> poly = [this](T _x) -> T {
      return _x;
    };

    return poly;
  }

};

#endif
