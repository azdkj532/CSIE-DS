#include <iostream>
#include <cstring>
#include <cassert> 

#include "./mystring.h"

void mystring::reallocate() 
{
    size_t _new_size = _size << 1;
    assert(_new_size >> 1 == _size);
    char* _new_data = new char[_new_size];
    assert(_new_data != 0);
    strncpy(_new_data, _data, _size);
    delete _data;
    _data = _new_data;
    _end = _data;
}

int mystring::set(char* str, size_t n) {
    strncpy(_data, str, n);
    _end = _data + n;
    return 0;
}

int mystring::_rolling_checksum_a(size_t length)
{
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += at(i);
    }
    return sum;
}

int mystring::_rolling_checksum_b(size_t length)
{
    int sum = 0;
    for (int i = 0; i < length ; i++) {
        sum += (length - i) * at(i);
    }
    return sum;
}

int mystring::frequency(const mystring& str)
{
    int find = 0, rolling_a = 0, rolling_b = 0;
    int str_rolling_a = 0, str_rolling_b = 0;

}

char& mystring::at(int i) const
{
    if (i >= 0) {
        assert(_data + i < _end);
        return *(_data + i);
    } else {
        assert(_end + i >= _data);
        return *(_end + i);
    }
}

char mystring::operator [] (int i) const 
{
    return this->at(i);
}

char& mystring::operator [] (int i)
{
    return this->at(i);
}

rolling_checksum::rolling_checksum(const mystring &str, size_t n):
    sum_a(0), sum_b(0), size(n)
{
    for (int i = 0; i < n; i++) {
        sum_a += static_cast<int>(str[i]);
        sum_b += (n-i) * static_cast<int>(str[i]);
    }
    sum_a %= _MOD;
    sum_b %= _MOD;
}

int rolling_checksum::next(char head, char tail)
{
    sum_a -= static_cast<int>(head);
    sum_a += static_cast<int>(tail);

    sum_b -= size * static_cast<int>(head);
    sum_b += sum_a;

    sum_a %= _MOD;
    sum_b %= _MOD;
    return get();
}
