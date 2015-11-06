#include <iostream>
#include <cstring>
#include <cassert> 

#include "./mystring.h"

mystring::mystring(): _data(0), _end(0), _capacity(10) {
    _data = new char[_capacity];
    _end = _data;
    assert(_data != 0);
}

mystring::~mystring()
{
    delete _data;
}

void mystring::reallocate() 
{
    size_t _new_capacity = _capacity * 2;
    assert(_new_capacity > _capacity);
    char* _new_data = new char[_new_capacity];
    assert(_new_data != 0);
    size_t len = length();
    strncpy(_new_data, _data, len);
    delete _data;
    _data = _new_data;
    _end = _data + len;
    _capacity = _new_capacity;
}

int mystring::set(char* str, size_t n) {
    if (n >= _capacity) {
        reallocate();
    }
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
    int appears_amount = 0;
    /* initialize the rolling checksum */ 
    rolling_checksum checksum_target(str.length());
    for (int i = 0; i < str.length(); ++i) {
        checksum_target.ismatch(str[i]);
    }
    int hash = checksum_target.hash();
    rolling_checksum checksum(str.length());
    for (int i = 0; i < length(); ++i) {
        if (checksum.ismatch(_data[i], hash)) {
            /* if checksum matched, we do more detailly matching test. */
            bool match = true;
            for (int j = 0; j < str.length(); j++) {
                if (at(i-j) != str[-j-1]) {
                    match = false;
                }
            }
            if (match) {
                /* I can do what I want here*/
                ++appears_amount;
            }
        }
    }
    return appears_amount;
}

mystring& mystring::remove(const mystring &str)
{
    if (length() < str.length()) {
        // won't match any thing
        return *this;
    }
    
    /* initialize the rolling checksum */ 
    rolling_checksum checksum_target(str.length());
    for (int i = 0; i < str.length(); ++i) {
        checksum_target.ismatch(str[i]);
    }
    int hash = checksum_target.hash();
    rolling_checksum checksum(str.length());
    for (int i = 0; i < length(); ++i) {
        if (checksum.ismatch(_data[i], hash)) {
            /* if checksum matched, we do more detailly matching test. */
            bool match = true;
            for (int j = 0; j < str.length(); j++) {
                if (at(i-j) != str[-j-1]) {
                    match = false;
                }
            }
            if (match) {

                /* I can do what I want here*/
                strncpy(_data+i-str.length()+1, _data+i+1, _end - (_data+i+1));
                checksum.clear();
                --i; // compute this byte again
                _end -= str.length();
            }
        }
    }
    return *this;
} // remove

mystring& mystring::replace(const mystring& str, const mystring& dst)
{
    if (length() < str.length()) {
        // won't match any thing
        return *this;
    }
    
    /* initialize the rolling checksum */ 
    rolling_checksum checksum_target(str.length());
    for (int i = 0; i < str.length(); ++i) {
        checksum_target.ismatch(str[i]);
    }
    int hash = checksum_target.hash();
    rolling_checksum checksum(str.length());
    for (int i = 0; i < length(); ++i) {
        if (checksum.ismatch(_data[i], hash)) {
            /* if checksum matched, we do more detailly matching test. */
            bool match = true;
            for (int j = 0; j < str.length(); j++) {
                if (at(i-j) != str[-j-1]) {
                    match = false;
                }
            }
            if (match) {

                /* I can do what I want here*/
                if (length() + dst.length() - str.length() >= _capacity) {
                    reallocate();
                }
                int delta = dst.length() - str.length();
                char *buff = new char [length() + dst.length()];
                strncpy(buff, _data+i+1, _end - (_data+i+1));
                strncpy(_data+i-str.length()+1, dst._data, dst.length());
                strncpy(_data+i+delta+1, buff, _end - (_data+i+1));
                delete buff;
                checksum.clear();
                _end += delta;
            }
        }
    }
    return *this;
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

std::ostream& operator << (std::ostream& os, const mystring & str)
{
    for (int i = 0; i < str.length(); ++i) {
        os << str._data[i];
    }
    return os;
}

bool mystring::operator== (const mystring &str)
{
    if (str.length() == length()) {
        for (int i = 0; i < length(); ++i) {
            if (_data[i] != str[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}
/*
 * rolling checksum algorithm
 *
 * */

rolling_checksum::rolling_checksum(size_t n):
    sum_a(0), sum_b(0), size(0)
{
    _buffer = _bufferPtr = new char[n];
    _bufferEnd = _buffer + n;
}

rolling_checksum::~rolling_checksum()
{
    delete _buffer;
}

char* rolling_checksum::nextPtr(char *ptr)
{
    return (ptr+1 >= _bufferEnd) ? _buffer : ptr+1;
}

char* rolling_checksum::prevPtr(char *ptr)
{
    return (ptr-1 < _buffer) ? _bufferEnd-1: ptr-1;
}

bool rolling_checksum::ismatch(char c, int target)
{
    if (size < _bufferEnd - _buffer) {
        *_bufferPtr = c;
        ++size;
        _bufferPtr = nextPtr(_bufferPtr);
        if (size == _bufferEnd - _buffer) {
            // initialize the checksum list
            char* p = prevPtr(_bufferPtr);
            sum_a = sum_b = 0;
            for (int i = 0; i < size; ++i) {
                sum_a += static_cast<int>(*p);
                sum_b += (i+1) * static_cast<int>(*p);
                p = prevPtr(p);
            }
        } else {
            return false;
        }
    } else {
        sum_a += static_cast<int>(c);
        sum_a -= *_bufferPtr;

        sum_b += sum_a;
        sum_b -= size * static_cast<int>(*_bufferPtr);

        sum_a %= _MOD;
        sum_b %= _MOD;

        *_bufferPtr = c;
        _bufferPtr = nextPtr(_bufferPtr);

    }
    if (target == hash()) {
        return true;
    } else {
        return false;
    }
}

int rolling_checksum::hash()
{
    if (_bufferEnd - _buffer == size) {
        return (sum_a + (2<<16)*sum_b) % _MOD;
    } else {
        return 0;
    }
}
