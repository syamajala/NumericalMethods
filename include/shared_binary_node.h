#ifndef SHARED_BINARY_NODE_H
#define SHARED_BINARY_NODE_H
#include <memory>

/*
 * A node can have more than one parent.
 *
 *          D
 *         / 
 *       B-
 *     /   \
 *  A -     E
 *     \   /
 *       C-
 *         \
 *          F
 */

using namespace std;

template <class T>
class SharedBinaryNode {
 private:
  shared_ptr< SharedBinaryNode<T> > lchild;
  shared_ptr< SharedBinaryNode<T> > rchild;
  T val;
 public:
  SharedBinaryNode<T>(const shared_ptr< SharedBinaryNode<T> > lchild,
		      const shared_ptr< SharedBinaryNode<T> > rchild,
		      const T data) : lchild(lchild), rchild(rchild), val(val) {};
  SharedBinaryNode<T>(T val) : lchild(nullptr), rchild(nullptr), val(val) {};

  shared_ptr< SharedBinaryNode<T> > get_lchild() { return lchild; };
  shared_ptr< SharedBinaryNode<T> > get_rchild() { return rchild; };

  void set_child(const shared_ptr< SharedBinaryNode<T> > child, bool left = true) {
    if(left)
      lchild = child;
    else
      rchild = child;
  };

  void set_val(T v) { val = v; };
  T get_val() { return val; };
};
#endif
