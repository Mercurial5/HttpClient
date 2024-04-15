#include <iostream>
#include <string>

#include "request.h"
#include "url.h"


int main() {
    URL url("https://dummyapi.io:80/data/v1/");

    std::string message = "GET " + url.path() + " HTTP/1.1\n\n";
    message += "host: " + url.netloc().host;

    Request request (url);
    std::string response = request.send(message);

    std::cout << response << std::endl;

    return 0;
}
