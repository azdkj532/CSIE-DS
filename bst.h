#ifndef BST_H_
#define BST_H_

#include <cassert>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>

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

    BSTNode<T> * leftChild() {return reinterpret_cast<BSTNode<T>*>(_left & MASK); }
    BSTNode<T> * rightChild() {return reinterpret_cast<BSTNode<T>*>(_right & MASK); }
    BSTNode<T> * leftChild(BSTNode<T> * newPtr) {
        _left = reinterpret_cast<size_t>(newPtr) | (_left & 1);
        return this;
    }
    BSTNode<T> * rightChild(BSTNode<T> * newPtr) {
        _right = reinterpret_cast<size_t>(newPtr) | (_right & 1);
        return this;
    }

    bool isRightThread() { return _right & 1; }
    bool isLeftThread() { return _left & 1; }

    void setRightFlag(bool f) { _right = (_right & MASK) | f; }
    void setLeftFlag(bool f) { _left = (_left & MASK) | f; }

    inline bool isLeaf() { return isLeftThread() && isRightThread(); }
    T& value() { return _value; }
};

template<typename T>
class BSTree {
 protected:
    BSTNode<T> * _root;

 public:
    BSTree(): _root(0) {}

    class iterator {
        friend class BSTree<T>;
        BSTNode<T> * _node;

        BSTNode<T> * next() {
            if (_node->isRightThread()) {
                // right thread
                return _node->rightChild();
            } else {
                // right child
                BSTNode<T> * current = _node->rightChild();
                while (!current->isLeftThread())
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
                while (!current->isRightThread())
                    current = current->rightChild();
                return current;
            }
        }

     public:
        explicit iterator(BSTNode<T> * ptr = 0): _node(ptr) {}
        iterator(const iterator & it): _node(it._node) {}
        ~iterator() {}

        const T operator * () const { return _node->_value; }
        T& operator * () { return _node->_value; }
        iterator& operator = (const iterator & it) { _node = it._node; return *this; }
        iterator& operator++ () { _node = next(); return *(this); }
        iterator operator++ (int) { auto ret = *(this); _node = next(); return ret; }
        iterator& operator-- () { _node = prev(); return *(this); }
        iterator operator-- (int) { auto ret = *(this); _node = prev(); return ret; }

        bool operator== (const iterator& it) const { return (it._node == _node); }
        bool operator!= (const iterator& it) const { return !(it == *(this)); }

        iterator lchild() {
            if (_node->isLeftThread()) {
                return iterator(0);
            } else {
                return iterator(_node->leftChild());
            }
        }
        iterator rchild() {
            if (_node->isRightThread()) {
                return iterator(0);
            } else {
                return iterator(_node->rightChild());
            }
        }
    };

    friend std::ostream& operator<< (std::ostream& os, BSTree<T>& bst) {
        std::queue<BSTree<T>::iterator> q;
        int stage = 1, next_stage = 0;
        q.push(BSTree<T>::iterator(bst._root));
        static const BSTree<T>::iterator nul = BSTree<T>::iterator(0);
        while (!q.empty()) {
            BSTree<T>::iterator it = q.front();
            q.pop();
            if (it._node != 0) {
                os << *it << " ";
                q.push(it.lchild());
                q.push(it.rchild());
                next_stage += 2;
            } else {
                os << "X ";
            }
            if (!--stage) {
                os << std::endl;
                stage = next_stage;
                next_stage = 0;
            }
        }
        return os;
    }

    bool empty() { return _root == 0; }
    iterator bottom() {
        assert(_root != 0);
        iterator it(_root);
        while (it.prev() != _root) {
            it._node = it.prev();
        }
        return it;
    }
    iterator top() {
        assert(_root != 0);
        iterator it(_root);
        while (it.next() != _root) {
            it._node = it.next();
        }
        return it;
    }
    void pop() { auto it = top(); remove(it); }
    
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
                else
                    currentNode = currentNode->rightChild();
            } else {
                if (currentNode->isLeftThread())
                    break;
                else
                    currentNode = currentNode->leftChild();
            }
        }
        it = iterator(currentNode);
        return false;
    }
    iterator insert(const T& source) {
        if (empty()) {
            // create vary first node
            _root = new BSTNode<T>(source);
            _root->rightChild(_root);
            _root->setRightFlag(true);
            _root->leftChild(_root);
            _root->setLeftFlag(true);
            return BSTree<T>::iterator(_root);
        }

        BSTree<T>::iterator it;
        bool isFind = find(source, it);
        BSTNode<T> * currentNode = it._node;
        BSTNode<T> * newNode = new BSTNode<T>(source);
        newNode->setRightFlag(true);
        newNode->setLeftFlag(true);
        if (*it < source) {
            newNode->rightChild(currentNode->rightChild());
            newNode->leftChild(currentNode);
            currentNode->rightChild(newNode);
            currentNode->setRightFlag(false);
        } else {
            newNode->leftChild(currentNode->leftChild());
            newNode->rightChild(currentNode);
            currentNode->leftChild(newNode);
            currentNode->setLeftFlag(false);
        }
        return iterator(newNode);
    }

    void remove(const T& source) {
        iterator it;
        bool isFind = find(source, it);

        if (isFind) {
            remove(it);
        }
    }

    void remove(iterator& it) {
        BSTNode<T> * currentNode = it._node;
        if (currentNode->_repeat > 1) {
            --currentNode->_repeat;
        } else if (!currentNode->isRightThread()) {
            iterator s = iterator(it.next());
            std::swap(*s, *it);
            std::swap(s._node->_repeat, it._node->_repeat);
            remove(s);
        } else if (!currentNode->isRightThread()) {
            iterator s = iterator(it.prev());
            std::swap(*s, *it);
            std::swap(s._node->_repeat, it._node->_repeat);
            remove(s);
        } else {
            // delete a leaf node
            BSTNode<T> * nextNode = it.next();
            BSTNode<T> * prevNode = it.prev();
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
