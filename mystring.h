#ifndef MYSTRING_H_
#define MYSTRING_H_

#include <iostream>
#include <cstring>
#include <cassert> 

class mystring {
 public:

    mystring(): _data(0), _end(0), _size(10) {
        _data = new char[10];
        assert(_data != 0);
    }
    ~mystring() {
        delete _data;
    }

    int set(char* str, size_t n);
    int hash(size_t size=5);
    int length() const { return _size; }

    // functions that spec required
    int frequency(const mystring &str);
    mystring& remove(const mystring &str);
    mystring& replace(const mystring& src, const mystring& dst);

    // overload operators
    char operator [] (int i) const;
    char& operator [] (int i);
         
 private:

    char* _data;
    char* _end;
    size_t _size;
    void reallocate();
    char& at(int i) const;
    int _rolling_checksum_a(size_t len);
    int _rolling_checksum_b(size_t len);

};

class rolling_checksum
{
 public:

    static const int _MOD = 100007;
    rolling_checksum(const mystring &str, size_t n);
    rolling_checksum(char* begin, size_t n);
    int get(){ return (sum_a + (2<<16) * sum_b) % _MOD; }
    int next(char head, char tail);
    int sum_a, sum_b;
    const int size;
};

#endif // MYSTRING_H_
