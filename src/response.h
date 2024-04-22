#pragma once

#include <map>
#include <string>
#include <sstream>

class Response {
    public:
        int status_code;
        std::string body;
        std::map<std::string, std::string> headers;

        Response(std::stringstream&);
};
