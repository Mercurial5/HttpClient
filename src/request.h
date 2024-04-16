#pragma once

#include <string>
#include <map>

#include "url.h"

class Request {
    URL _url;
    std::map<std::string, std::string> _headers;

    public:
        Request(URL);
        Request(URL, std::map<std::string, std::string> headers);

        URL url();
        
        void update_headers(std::map<std::string, std::string>);
        std::map<std::string, std::string> headers();

        std::string http(); 
};
