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
    void counting(element* current=0) {
        if (current == 0) current = _root;
        if (current->isLeaf()) return;
        if (!current->isLeftThread()) {
            counting(current->leftChild());
            current->value().left = current->leftChild()->value().total();
        }
        if (!current->isRightThread()) {
            counting(current->rightChild());
            current->value().right = current->rightChild()->value().total();
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

    while (true) {
        cout << "the average of the lagrest kth elements. Input k (-1 to exit):" << endl;
        int k;
        cin >> k;
        if (k == -1)
            break;
        int sum = 0, countable = 0;
        auto it = bst.top();
        for (int i = 0; i < k; i++) {
            sum += (*it).value;
            if (it == bst.bottom()) {
                countable = false;
                break;
            } else {
                countable = true;
                --it;
            }
        }

        cout << "average is ";
        if (countable) {
            cout << (double)sum / k << endl;
        } else {
            cout << -1 << endl;
        }

    }
    return 0;
}
