#include "shared_binary_node.h"

using namespace std;

template <class T>
using Node = SharedBinaryNode<T>;
template <class T>
using NodePtr = shared_ptr< SharedBinaryNode<T> >;

template <class T>
class SharedBinaryTree {
 private:
  NodePtr<T> root;
 public:
  SharedBinaryTree() { root = nullptr; };
 SharedBinaryTree(NodePtr<T> root) : root(root) {};
 SharedBinaryTree(T val) : root(NodePtr<T>(new Node<T>(val))) {};

  NodePtr<T> insert_child(T val, bool left = true, NodePtr<T> node = nullptr) {
    NodePtr<T> child(new Node<T>(val));

    if(root == nullptr) {
      root = child;
      return child;
    }
    
    if(node)
      node->set_child(child, left);
    else
      root->set_child(child, left);
    return child;
  }

  NodePtr<T> insert_shared_child(T val,
				 NodePtr<T> lnode,
				 NodePtr<T> rnode,
				 bool lnode_rchild = true,
				 bool rnode_lchild = true) {
    NodePtr<T> child(new Node<T>(val));
    if(lnode_rchild && rnode_lchild) {
      lnode->set_child(child, false);
      rnode->set_child(child, true);
    }    
  }
};

/* #include "shared_binary_tree.h" */
/* #include "shared_binary_node.h" */
 
/* typedef SharedBinaryNode<double> DBLNODE ; */
/* typedef shared_ptr<DBLNODE> DBLNODEPTR; */

/* int main() { */
/*   SharedBinaryTree<double> tree(0.0); */
/*   DBLNODEPTR lchild1 = tree.insert_child(1.0); */
/*   DBLNODEPTR rchild1 = tree.insert_child(2.0); */
/*   DBLNODEPTR shared_child = tree.insert_child(3.0, false, lchild1);   */
/* } */
