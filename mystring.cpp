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

int mystring::frequency(const mystring& str)
{
    if (length() < str.length()) {
        // won't match any thing
        return 0;
    }
    // initialize the rolling checksum
    rolling_checksum checksum_target(str, str.length());
    rolling_checksum checksum(*this, str.length());
    int appears_amount = 0,
        delta = this->length() - str.length();
    for (int i = 0; i < delta; i++) {
        checksum.next(this->at(i), this->at(i+str.length()));
        if (checksum.get() == checksum_target.get()) {
            // if checksum matched, we do more detailly matching test.
            bool match = true;
            for (int j = 0; j < str.length(); j++) {
                if (at(i+j) != str[j]) {
                    match = false;
                }
            }
            if (match) {
                ++appears_amount;
            }
        }
    }
    return appears_amount;
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
