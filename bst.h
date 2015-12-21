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
    static  const size_t MASK = ~(0x1);

 public:
    BSTNode<T> * leftChild() {return static_cast<BSTNode<T>*>(_left & MASK); }
    BSTNode<T> * rightChild() {return static_cast<BSTNode<T>*>(_right & MASK); }
    BSTNode<T> * leftChild(BSTNode<T> * newPtr) {
        _left = static_cast<size_t>(newPtr) | (_left & 1);
        return this;
    }
    BSTNode<T> * rightChild(BSTNode<T> * newPtr) {
        _right = static_cast<size_t>(newPtr) | (_right & 1);
        return this;
    }

    bool isRightThread() { return _right & 1; }
    bool isLeftThread() { return _left & 1; }
    inline bool isLeaf() { return isLeftThread() && isRightThread(); }
};

template<typename T>
class BSTree {
    BSTNode<T> * _root;

 public:
};
#endif  // BST_H_
