#ifndef DIFFERENCE_H
#define DIFFERENCE_H

#include "fit.h"

using namespace std;

template <class T>
class DividedDifference : public Fit<T> {

protected:
  vector<vector<T>> table;

  void build_table(const T point, const int deg) {
    vector<int> nnIdx = this->neighbors(point, deg+1);
    vector<T> sx;

    // n = 0
    vector<T> zero_nodes;
    for(auto i : nnIdx) {
      sx.push_back(this->x[i]);
      zero_nodes.push_back(this->f[i]);
    }

    table.push_back(zero_nodes);

    for(int n = 1; n <= deg+1; n++) {
      vector<T> n_nodes;
      for(size_t i = 0; i < table[n-1].size() - 1; i++) {
        n_nodes.push_back((table[n-1][i+1] - table[n-1][i]) / (sx[n+i] - sx[i]));
      }
      table.push_back(n_nodes);
    }
    table.insert(table.begin(), sx);
  };

public:
 DividedDifference(const vector<T> &x, const vector<T> &f) : Fit<T>(x, f) {};

  function<T (T)> fit(const T point, const int deg) {
    this->build_table(point, deg);

    function<T (T)> poly = [&, deg](T _x) -> T {
      T s = this->table[1][0];
      for(int n = 1; n <= deg+1; n++) {
        T p = 1;
        for(int i = 0; i < n; i++) {
          p *= (_x - this->table[0][i]);
        }
        s += (p*this->table[n+1][0]);
      }
      return s;
    };

    return poly;
  };

};

#endif
