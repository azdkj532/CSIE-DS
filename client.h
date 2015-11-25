/*
 * Copyright © 2015 Squirrel Larry
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef CLIENT_H_
#define CLIENT_H_

#include <list>
class Client {
 public:
     Client(int a, int b, int c):
         _arrival_time(a), _service_time(b), _deadline(c), _delay(0) {}
     bool deadline_test(int time);
     void set_start_time(int time);
     enum {
         MAX_TIME = 9999
     };
     int departure_time() const;
     int service_time() const { return _service_time; }
     int arrival_time() const { return _arrival_time; }
 private:
     int _arrival_time;
     int _service_time;
     int _deadline;
     int _delay;
};
#endif // CLIENT_H_
