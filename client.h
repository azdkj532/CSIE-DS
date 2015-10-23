#include <iostream>

#ifndef CLIENT_H_
#define CLIENT_H_

class Client {
 public:
     friend bool operator < (const Client &a, const Client &b);
     friend bool operator << (ostream &os, const Client &a);
 private:
     int _arrival_time;
     int _waiting_limit;
     int _service_time;
     int _service_start_time;
};

#endif // CLIENT_H_
