#include <iostream>
#include <string>
#include <sstream>
#include "./bst.h"

using std::cout;
using std::cin;
using std::ends;
using std::endl;
using std::string;

int menu() {
    cout << endl;
    cout << "=========================================" << endl;
    cout << "[1] insert a value" << std::endl;
    cout << "[2] remove a value" << std::endl;
    cout << "[3] pop max" << std::endl;
    cout << "[4] print tree" << std::endl;
    cout << "[0] Exit" << std::endl;
    cout << "=========================================" << endl;
    string line;
    getline(cin, line);
    for (auto i : line) {
        switch (i) {
            case '1':
                return 1;
            case '2':
                return 2;
            case '3':
                return 3;
            case '4':
                return 4;
        }
    }
    return 0;
}

int main(int argc, char const* argv[]) {
    cout << "Please input a sequence of integer, and using ' ' as delimiter" << endl;
    string line;
    getline(cin, line);
    std::stringstream ss(line);

    int num;
    BSTree<int> bst;
    while (ss >> num) {
        bst.insert(num);
    }

    int action;
    do {
        action = menu();
        int tmp;
        switch (action) {
            case 1:
                // insert
                cout << "What do you want to insert? ";
                cin >> tmp;
                bst.insert(tmp);
                break;
            case 2:
                // remove
                cout << "What do you want to remove? ";
                cin >> tmp;
                bst.remove(tmp);
                break;
            case 3:
                // pop
                if (bst.empty()) {
                    cout << "Nothing to pop" << endl;
                } else {
                    cout << *bst.top() << " popped" << endl;
                    bst.pop();
                }
                break;
            case 4:
                // print
                cout << bst << endl;
                break;
        }
        cin.ignore();
    } while (action);
    cout << "Bye~" << endl;
    return 0;
}
