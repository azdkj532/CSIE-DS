#include <iostream>
#include <vector>

#include "./client.h"

int main(int argc, char *argv[]) {

    std::vector<Client*> data;
    std::vector<Client*> queue;

    Client* empty_job = new Client(0, 0, 0);
    data.push_back(empty_job);  // empty jobs
    queue.push_back(empty_job);
    Client* empty_job = new Client(0, 0, 0);
    data.push_back(empty_job);  // empty jobs
    queue.push_back(empty_job);

    while (true) {
        int arrival, service, deadline;
        std::cin >> arrival;
        if (arrival == 0) break;
        std::cin >> service >> deadline;
        Client *client = new Client(arrival, service, deadline);
        data.push_back(client);
        if (client->deadline_test(queue.back()->departure_time())) {
            // clien found it can meet its deadline
            // client join the procession at the end
            client->set_start_time(queue.back()->departure_time());
            queue.push_back(client);
        } else {
            Client* least = queue.back();
            queue.pop_back();
            client->set_start_time(queue.back()->departure_time());
            if (client->deadline_test(queue.back()->departure_time()) &&
                    least->deadline_test(client->departure_time())) {
                // clien cutin the last client
                client->set_start_time(queue.back()->departure_time());
                queue.push_back(client);
                least->set_start_time(queue.back()->departure_time());
                queue.push_back(least);
            } else {
                // what ever he does wont meet the deadline,
                // so the client leave.
                client->set_start_time(Client::MAX_TIME);
                least->set_start_time(queue.back()->departure_time());
                queue.push_back(least);
            }
        }
    }
    for (auto it : data) {
        //std::cout << it->_arrival_time << " " << it->_service_time << " ";
        //std::cout << it->departure_time() << std::endl;
    }
    for (auto it : data) {
        delete it;
    }
    data.clear();
    return 0;
}
