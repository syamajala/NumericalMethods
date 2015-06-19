#include <map>
#include "fit.h"
#include "shared_binary_tree.h"
#include "shared_binary_node.h"

using namespace std;

template <class T>
class Neville : public Fit<T> {
 private:
  vector<vector<T>> nodes;
  
  void build_table(const T point, const int deg) {
    vector<int> nnIdx = this->neighbors(point, deg);
    //    vector<vector<T>> nodes;
    vector<T> sx;

    // n = 0
    vector<T> zero_nodes;
    for(auto i : nnIdx) {
      sx.push_back(this->x[i]);
      zero_nodes.push_back(this->f[i]);
    }
    nodes.push_back(zero_nodes);

    int depth = 1;
    for(int n = 1; n < deg+1; n++) {
      vector<T> n_nodes;

      for(size_t i = 0; i < nodes[n-1].size() - 1; i++) {
	T a = (point - sx[i])*(nodes[n-1][i+1]);
	T b = (point - sx[i+n])*(nodes[n-1][i]);
	T c = (sx[i+n] - sx[i]);
	T val = (a - b)/c;
	n_nodes.push_back(val);
      }
      nodes.push_back(n_nodes);
      depth++;
    }
  };
  
 public:
 Neville(const vector<T> &x, const vector<T> &f) : Fit<T>(x, f) {};

  function<T (T)> fit(const T point, const int deg) {
    this->build_table(point, deg);

    function<T (T)> poly = [this](T _x) -> T {
      return (nodes.back()).back();
    };
    return poly;
  };
  
};
