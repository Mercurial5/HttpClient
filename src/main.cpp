#include <iostream>
#include <string>

#include "client.h"
#include "request.h"
#include "url.h"


int main() {
    URL url("http://ip-api.com:80/json/");
    Request request(url);

    try {
        std::string response = Client::send(url);
        std::cout << "Response: " << response << std::endl;
    } catch (Client::ClientError &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
