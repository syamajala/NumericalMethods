#ifndef NEVILLE_H
#define NEVILLE_H

#include <map>
#include "fit.h"

using namespace std;

template <class T>
class Neville : public Fit<T> {
 private:
  vector<vector<T>> table;

  void build_table(const T point, const int deg) {
    vector<int> nnIdx = this->neighbors(point, deg);
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
        T a = (point - sx[i])*(this->table[n-1][i+1]);
        T b = (point - sx[i+n])*(this->table[n-1][i]);
        T c = (sx[i+n] - sx[i]);
        T val = (a - b)/c;
        n_nodes.push_back(val);
      }
      this->table.push_back(n_nodes);
    }
  };

 public:
 Neville(const vector<T> &x, const vector<T> &f) : Fit<T>(x, f) {};

  function<T (T)> fit(const T point, const int deg) {
    this->build_table(point, deg);

    function<T (T)> poly = [this](T _x) -> T {
      return (this->table.back()).back();
    };
    return poly;
  };
};

#endif
