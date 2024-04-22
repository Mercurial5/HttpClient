#include <iostream>
#include <string>
#include <sstream>

#include "client.h"
#include "request.h"
#include "response.h"
#include "url.h"

int main() {
    URL url("http://ip-api.com:80/json/");
    Request request(url);

    try {
        Response response = Client::send(url);

        std::cout << "Status code: " << response.status_code << std::endl;
        std::cout << "Headers: " << std::endl;
        for (auto& i: response.headers) {
            std::cout << '\t' << i.first << ": " << i.second << std::endl;
        }
        std::cout << std::endl << "Body: " << response.body << std::endl;
    } catch (Client::ClientError &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
