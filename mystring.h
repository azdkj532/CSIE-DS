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
     int frequency(const mystring &str);
     mystring& remove(const mystring &str);
     mystring& replace(const mystring& src, const mystring& dst);
     char operator [] (int i) const;
     char& operator [] (int i);

         
 private:
    char* _data;
    char* _end;
    size_t _size;
    void reallocate();
};

#endif // MYSTRING_H_
