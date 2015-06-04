#include <map>
#include "fit.h"
#include "shared_binary_tree.h"
#include "shared_binary_node.h"

using namespace std;

template <class T>
using Node =  SharedBinaryNode<T>;
template <class T>
using NodePtr = shared_ptr< SharedBinaryNode<T> >;

template <class T>
class Neville : public Fit<T> {
 private:  
  SharedBinaryTree<T> tree;

  void build_tree(const T point, const int deg) {
    vector<int> nnIdx = this->neighbors(point, deg+1);
    vector< vector< NodePtr<T> > > nodes;
    vector<T> sx;

    // n = 0
    vector< NodePtr<T> > zero_nodes;
    for(auto i : nnIdx) {
      sx.push_back(this->x[i]);
      zero_nodes.push_back(NodePtr<T>(new Node<T>(this->f[i])));
    }
    nodes.push_back(zero_nodes);

    int depth = 1;
    for(int n = 1; n < deg+1; n++) {
      vector< NodePtr<T> > n_nodes;
      for(size_t i = 0; i < nodes[n-1].size() - 1; i++) {
	T a = (point - sx[i])*(nodes[n-1][i+1]->get_val());
	T b = (point - sx[i+n])*(nodes[n-1][i]->get_val());
	T c = (sx[i+n] - sx[i]);
	T val = (a - b)/c;
	cout << "f(" << i << ", " << n << ") = " << val << endl; 
	n_nodes.push_back(NodePtr<T>(new Node<T>(val)));
      }
      nodes.push_back(n_nodes);
      depth++;
    }
  };
  
 public:
 Neville(const vector<T> &x, const vector<T> &f) : Fit<T>(x, f) {};

  function<T (T)> fit(const T point, const int deg) {
    this->build_tree(point, deg);

    function<T (T)> poly = [](T _x) -> T {
      return 0.0;
    };
    return poly;
  };
  
};
