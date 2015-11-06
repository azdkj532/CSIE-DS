#ifndef MYSTRING_H_
#define MYSTRING_H_

#include <ostream>
#include <cstring>
#include <cassert> 

class mystring {
 public:

    mystring();
    ~mystring();

    int set(char* str, size_t n);
    int hash(size_t size=5);
    int length() const { return _end-_data; }
    char append(char c);

    // functions that spec required
    int frequency(const mystring &str);
    mystring& replace(const mystring& src, const mystring& dst);

    // overload operators
    char operator [] (int i) const;
    char& operator [] (int i);
    bool operator== (const mystring &str);

    friend std::ostream& operator << (std::ostream& os, const mystring & str);
         
 private:

    char* _data;
    char* _end;
    size_t _capacity;
    void reallocate();
    char& at(int i) const;
    int _rolling_checksum_a(size_t len);
    int _rolling_checksum_b(size_t len);

};

class rolling_checksum
{
 public:

    static const int _MOD = 10000007;
    rolling_checksum(size_t n);
    ~rolling_checksum();
    bool ismatch(char c, int hash=0);
    int hash();
    void clear() { size = 0; _bufferPtr = _buffer; }
 private:
    char* nextPtr(char *ptr);
    char* prevPtr(char *ptr);

    char *_buffer, *_bufferEnd, *_bufferPtr;
    int sum_a, sum_b;
    int size;
};

#endif // MYSTRING_H_
