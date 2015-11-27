#include <iostream>
#include <iomanip>
#include <vector>

#include "./client.h"

int main(int argc, char *argv[]) {

    std::vector<Client*> data;
    std::vector<Client*> queue;

    Client* empty_job = new Client(0, 0, 0);
    data.push_back(empty_job);  // empty jobs
    queue.push_back(empty_job);
    empty_job = new Client(0, 0, 0);
    data.push_back(empty_job);  // empty jobs
    queue.push_back(empty_job);

    std::cout << "          Arrival time  Service time  Allowable waiting time" << std::endl;
    int counter = 1;
    while (true) {
        std::cout << "Client " << counter++ << ": ";
        int arrival, service, deadline;
        std::cin >> arrival;
        if (arrival == 0) break;
        std::cin >> service >> deadline;
        Client *client = new Client(arrival, service, deadline);
        data.push_back(client);
    }
    for (auto it = data.begin()+2; it != data.end(); ++it) {
        Client * client = *it;
        if (client->deadline_test(queue.back()->departure_time())) {
            // clien found it can meet its deadline
            // client join the procession at the end
            client->set_start_time(queue.back()->departure_time());
            queue.push_back(client);
        } else {
            Client* least = queue.back();
            queue.pop_back();
            if (client->deadline_test(queue.back()->departure_time()) &&
                    least->deadline_test(
                        std::max(client->arrival_time(), queue.back()->departure_time()) + client->service_time())) {
                // new client cut in to the queue, both least client and it meet their deadline
                client->set_start_time(queue.back()->departure_time());
                queue.push_back(client);
            } else {
                // client leave
                client->set_start_time(Client::MAX_TIME);
            }
            least->set_start_time(queue.back()->departure_time());
            queue.push_back(least);
        }
    }
    std::cout << "          Serverd or not?   Departure time" << std::endl;
    for (auto it=data.begin()+2; it != data.end(); ++it) {
        int departure_time = (*it)->departure_time();
        std::cout << "Client " << std::setw(2) << it - data.begin() - 1 << ":";
        if (departure_time == Client::MAX_TIME) {
#ifdef COLORFUL
            std::cout << "\x1b[31m";
#endif
            std::cout << std::setw(13) << "No";
#ifdef COLORFUL
            std::cout << "\x1b[0m";
#endif
        } else {
            std::cout << std::setw(13) << "Yes";
            if (departure_time > (*it)->arrival_time() + (*it)->waiting_time()) {
#ifdef COLORFUL
                std::cout << "\x1b[31m";
#endif
                std::cout << std::setw(10) << departure_time;
#ifdef COLORFUL
                std::cout << "\x1b[0m";
#endif
            } else {
                std::cout << std::setw(10) << departure_time;
            }
        }
        std::cout << std::endl;
    }
    // release all memory
    for (auto it : data) {
        delete it;
    }
    data.clear();
    queue.clear();
    return 0;
}
