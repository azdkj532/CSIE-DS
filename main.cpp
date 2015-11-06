#include <iostream>

#include "./mystring.h"

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char const* argv[])
{
#ifndef SELF_TEST
    cout << "hello, world" << endl;
#else
    char test[] = "qazwsxedcqazwsxedc";
    char target[] = "qaz";
    char dst[] = "1121";
    mystring str, str2, str3;
    str.set(test, 18);
    str2.set(target, 3);
    str3.set(dst, 4);

    assert(str.frequency(str2) == 2);
    assert(str.frequency(str3) == 0);

    mystring rem;
    char r[] = "wsxedcwsxedc";
    rem.set(r, 12);

    assert(str.remove(str2) == rem);

    mystring rep;
    char rr[] = "1121wsxedc1121wsxedc";
    rep.set(rr, 20);
    mystring str4;
    str4.set(test, 18);
    str4.replace(str2, str3);
    assert(rep == str4);

    cout << "All test passed!" << endl;
    return 0;
#endif
}
