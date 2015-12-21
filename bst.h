#ifndef BST_H_
#define BST_H_

#include <cctype>

template<typename T>
class BSTree;

template<typename T>
class BSTNode {
    friend class BSTree<T>;

    T _value;
    size_t _left;
    size_t _right;

 public:
    BSTNode<T> * leftChild() {return static_cast<BSTNode<T>*>(_left); }
    BSTNode<T> * rightChild() {return static_cast<BSTNode<T>*>(_right); }
    BSTNode<T> * leftChild(BSTNode<T> * newPtr) { _left = static_cast<size_t>(newPtr); return this; }
    BSTNode<T> * rightChild(BSTNode<T> * newPtr) { _right = static_cast<size_t>(newPtr); return this; }
};

template<typename T>
class BSTree {
    BSTNode<T> * _root;
};
#endif  // BST_H_
