#ifndef BST_H_
#define BST_H_

#include <cassert>
#include <cctype>
#include <algorithm>

template<typename T>
class BSTree;

template<typename T>
class BSTNode {
    friend class BSTree<T>;
    friend class BSTree<T>::iterator;

    T _value;
    size_t _left;
    size_t _right;
    size_t _repeat;
    static  const size_t MASK = ~(0x1);

 public:
    explicit BSTNode(const T& value = 0): _value(value), _left(0), _right(0), _repeat(1) {}

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

    void setRightFlag(bool f) { _right = (_right & MASK) | f; }
    void setLeftFlag(bool f) { _left = (_left & MASK) | f; }

    inline bool isLeaf() { return isLeftThread() && isRightThread(); }
};

template<typename T>
class BSTree {
    BSTNode<T> * _root;

 public:
    BSTree(): _root(0) {}

    class iterator {
        BSTNode<T> * _node;

        BSTNode<T> * next() {
            if (_node->isRightThread()) {
                // right thread
                return _node->rightChild();
            } else {
                // right child
                BSTNode<T> * current = _node->rightChild();
                while (current->isLeftThread())
                    current = current->leftChild();
                return current;
            }
        }
        BSTNode<T> * prev() {
            if (_node->isLeftThread()) {
                // left thread
                return _node->leftChild();
            } else {
                // left child
                BSTNode<T> * current = _node->leftChild();
                while (current->isLeftThread())
                    current = current->leftChild();
                return current;
            }
        }
     public:
        explicit iterator(BSTNode<T> * ptr = 0): _node(ptr) {}
        iterator(const iterator & it): _node(it._node) {}

        const T& operator * () const { return _node->_value; }
        T& operator * () { return _node->_value; }
        iterator& operator = (const iterator & it) { _node = it._node; return *this; }
        iterator& operator++ () { _node = next(); return _node; }
        iterator& operator++ (int o) { BSTNode<T> * ret = _node; _node = next(); return ret; }
        iterator& operator-- () { _node = prev(); return _node; }
        iterator& operator-- (int o) { BSTNode<T> * ret = _node; _node = prev(); return ret; }

        bool operator== (const iterator& it) { return (it._node == _node); }
        bool operator!= (const iterator& it) { return !(it == *(this)); }
    };

    bool empty() { return _root == 0; }
    iterator& begin() {
        assert(_root != 0);
        iterator it(_root), root(_root);
        while (it.prev() != root) {
            it = it.prev();
        }
        return it;
    }
    iterator& end() {
        assert(_root != 0);
        iterator it(_root), root(_root);
        while (it.next() != root) {
            it = it.next();
        }
        return it;
    }
    bool find(const T& source, iterator& it ) {
        if (empty()) {
            return false;
        }
        BSTNode<T> * currentNode = _root;

        while (true) {
            if (currentNode->_value == source) {
                it = iterator(currentNode);
                return true;
            } else if (currentNode->_value < source) {
                if (currentNode->isRightThread())
                    break;
                currentNode = currentNode->rightChild();
            } else {
                if (currentNode->isLeftThread())
                    break;
                currentNode = currentNode->leftChild();
            }
        }
        it = iterator(currentNode);
        return false;
    }
    iterator& insert(const T& source) {
        if (empty()) {
            // create vary first node
            _root = new BSTNode<T>(source);
            _root->rightChild(_root);
            _root->setRightFlag(true);
            _root->leftChild(_root);
            _root->setLeftFlag(true);
            return iterator(_root);
        }

        BSTree<T>::iterator it;
        bool isFind = find(source, it);
        if (isFind) {
            //just increase repeat amount
            ++it._node->_repeat;
        } else {
            BSTNode<T> * currentNode = it._node;
            BSTNode<T> * newNode = new BSTNode<T>(source);
            if (*it < source) {
                newNode->rightChild(currentNode->rightChild());
                newNode->setRightFlag(true);
                newNode->leftChild(currentNode);
                newNode->setLeftFlag(true);
                currentNode->setRightFlag(false);
            } else {
                newNode->leftChild(currentNode->leftChild());
                newNode->setLeftFlag(true);
                newNode->rightChild(currentNode);
                newNode->setRightFlag(true);
                currentNode->setLeftFlag(false);
            }
        }
    }

    bool remove(const T& source) {
        iterator it;
        bool isFind = find(source, it);

        if (isFind) {
            return remove(it);
        }
        return false;
    }

    void remove(iterator& it) {
        BSTNode<T> * currentNode = it._node;
        if (!currentNode->isRightThread()) {
            iterator s = it.next();
            std::swap(*s, *it);
            std::swap(s._node->_repeat, it._node->_repeat);
            remove(s);
        } else if (!currentNode->isRightThread()) {
            iterator s = it.prev();
            std::swap(*s, *it);
            std::swap(s._node->_repeat, it._node->_repeat);
            remove(s);
        } else {
            // delete a leaf node
            BSTNode<T> * nextNode = it.next()._node;
            BSTNode<T> * prevNode = it.prev()._node;
            if (nextNode == it._node) {
                // root node
                delete _root;
                _root = 0;
            } else if (nextNode->leftChild() == it._node) {
                nextNode->leftChild(it._node->leftChild());
                nextNode->setLeftFlag(true);
                delete it._node;
            } else if (prevNode->rightChild()) {
                prevNode->rightChild(it._node->rightChild());
                prevNode->setRightFlag(true);
                delete it._node;
            }
        }
    }
};

#endif  // BST_H_
