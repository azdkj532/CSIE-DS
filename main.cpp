#include <iostream>
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
    for (auto it : data) {
        std::cout << it->arrival_time() << " " << it->service_time() << " ";
        std::cout << it->departure_time() << std::endl;
    }
    for (auto it : data) {
        delete it;
    }
    data.clear();
    return 0;
}
