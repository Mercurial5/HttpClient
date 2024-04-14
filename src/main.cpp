#include <iostream>
#include "connection.h"

int main() {
    std::string host = "google.com";
    std::string port = "80";

    Connection* connection;	
    try {
        connection = new Connection(host, port);
    } catch (Connection::ConnectionError &e) {
        std::cout << e.what() << std::endl;
        return 0;
    }

    std::string message = "GET / HTTP/1.1\n\nhost: " + host;

    connection->send(message);
    std::string response = connection->read();

    std::cout << "Done" << std::endl;
    std::cout << response << std::endl;
    return 0;
}
