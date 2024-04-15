#include <iostream>
#include <string>

#include "request.h"
#include "url.h"


int main() {
    URL url("https://dummyapi.io:80/data/v1/");

    std::string response = Request::send(url);

    std::cout << response << std::endl;

    return 0;
}
