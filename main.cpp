#include <iostream>

#include "./mystring.h"

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char const* argv[])
{
    char test[] = "qazwsxedc";
    char target[] = "qaz";
    char dst[] = "111";
    mystring str, str2, str3;
    str.set(test, 9);
    str2.set(target, 3);
    str3.set(dst, 3);

    cout << str << endl;
    cout << str2 << endl;
    cout << str3 << endl;

    assert(str.frequency(str2) == 1);
    assert(str.frequency(str3) == 0);

    mystring rep;
    char r[] = "wsxedc";
    rep.set(r, 6);

    cout << str.remove(str2) << endl;
    cout << str.remove(str3) << endl;
    assert(str.remove(str2) == rep);

    mystring str4;
    str4.set(test, 9);
    cout << str4 << endl;
    cout << str4.replace(str2, str3) << endl;
    return 0;
}
