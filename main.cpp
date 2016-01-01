#include <utility>
#include <string>
#include <sstream>
#include <stack>
#include <queue>

#include "./bst.h"

struct count {
    explicit count(int a): value(a), right(0), left(0), visit(0) {}
    int value, right, left, visit;
    inline int total() { return right + left + 1; }
};

bool operator== (const count &a, const count &b) {
    return a.value == b.value;
}

bool operator< (const count &a, const count &b) {
    return a.value < b.value;
}

std::ostream& operator<< (std::ostream &os, const count &a) {
    return os << a.value;
}

class MyBST: public BSTree<count> {
    typedef BSTNode<count> element;
 public:
    void counting() {
        std::stack<element*> stk;
        stk.push(_root);
        while (!stk.empty()) {
            element * node = stk.top();
            if (node->value().visit == 1) {
                stk.pop();
                if (!node->isLeftThread()) {
                    node->value().left = node->leftChild()->value().total();
                }
                if (!node->isRightThread()) {
                    node->value().right = node->rightChild()->value().total();
                }
            } else {
                if (!node->isLeftThread()) {
                    stk.push(node->leftChild());
                }
                if (!node->isRightThread()) {
                    stk.push(node->rightChild());
                }
                node->value().visit = 1;
            }
        }
    }
    std::ostream& level_order_output(std::ostream &os) {
        std::queue<element*> qq;
        qq.push(_root);
        while (!qq.empty()) {
            element * node = qq.front();
            qq.pop();
            if (!node->isLeftThread()) {
                qq.push(node->leftChild());
            }
            if (!node->isRightThread()) {
                qq.push(node->rightChild());
            }
            os << node->value().left + 1<< " ";
        }
        return os;
    }
};

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char const* argv[]) {
    cout << "Please input a sequence of integer, and using ' ' as delimiter" << endl;
    string line;
    getline(cin, line);
    std::stringstream ss(line);

    int num;
    MyBST bst;
    while (ss >> num) {
        bst.insert(count(num));
    }

    bst.counting();
    bst.level_order_output(cout) << endl;
    cout << bst << endl;
    return 0;
}
