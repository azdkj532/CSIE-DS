#include <iostream>

#include "./mystring.h"

#define HR_LINE cout.write("==================================================\n", 51)

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char const* argv[])
{
#ifndef SELF_TEST
    HR_LINE;
    cout.write("=               Larry's CLI editor               =\n", 51);
    HR_LINE;
    cout << "\x1b[36mYou can key in the source string:\x1b[0m" << endl;

    mystring source;
    char c;
    while (cin.get(c), c != '\n') {
        // read char into mystring until \n appears.
        source.append(c);
    }

    bool quit = false;
    while (!quit) {
        //HR_LINE;
        cout << "supported command:\x1b[33m" << endl;
        cout << "* searching: /<string>" << endl;
        cout << "* replaceing: s/<target>/<dst>/" << endl;
        cout << "* removing: s/<target>//\x1b[0m" << endl;
        cout << endl;
        cout << "source string:" << endl;
        std::cout << source << endl;
        //HR_LINE;
        while (cin.peek() == ' ' || cin.peek() == '\n') cin.ignore();
        // s/asd/qwe/
        // /asd
        char c = cin.get();
        if (c == '/') {
            // searching command
            mystring target;
            while (cin.peek() != '\n') {
                char t = cin.get();
                target.append(t);
            }
            int f = source.frequency(target);
            cin.ignore();
            cout << target << " appears " << f << " times" << endl;
        } else if(c == 's') {
            char n = cin.get();
            if (n == '/') {
                // replace command
                mystring target;
                while (cin.peek() != '/') {
                    char t = cin.get();
                    if (t == '\\' && cin.peek() == '/') {
                        t = cin.get();
                    }
                    target.append(t);
                }
                cin.ignore();
                mystring dst;
                while (cin.peek() != '/') {
                    char t = cin.get();
                    if (t == '\\' && cin.peek() == '/') {
                        t = cin.get();
                    }
                    dst.append(t);
                }
                source.replace(target, dst);
                cout << source << endl;
            }
        } else if (c == 'q'){
            quit = true;
        }
        cin.unget();
        // ignore input
        cin.ignore(INT_MAX, '\n');
    }

#else
    char test[] = "qazwsxedcqazwsxedc";
    char target[] = "qaz";
    char dst[] = "1121";

    mystring str, str2, str3, non;
    str.set(test, 18);
    str2.set(target, 3);
    str3.set(dst, 4);

    assert(str.frequency(str2) == 2);
    assert(str.frequency(str3) == 0);

    mystring rem;
    char r[] = "wsxedcwsxedc";
    rem.set(r, 12);

    assert(str.replace(str2, non) == rem);

    mystring rep;
    char rr[] = "1121wsxedc1121wsxedc";
    rep.set(rr, 20);
    mystring str4;
    str4.set(test, 18);
    str4.replace(str2, str3);
    assert(rep == str4);

    mystring app;
    app.append('1');
    app.append('1');
    app.append('2');
    app.append('1');

    assert(app == str3);
    cout << "All test passed!" << endl;
    return 0;
#endif
}
