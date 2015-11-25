#include <algorithm>

#include "./client.h"

bool Client::deadline_test(int time) {
    // test client will meet deadline or not when it starts at `time`
    if (std::max(_arrival_time, time) + _service_time <= _arrival_time + _deadline) {
        return true;
    }
    return false;
}

void Client::set_start_time(int time) {
    if (time == MAX_TIME) {
        _delay = MAX_TIME;
    } else {
        _delay = (time > _arrival_time) ? time - _arrival_time : 0;
    }
}

int Client::departure_time() const {
    if (_delay != MAX_TIME)
        return _arrival_time + _delay + _service_time;
    return MAX_TIME;
}
