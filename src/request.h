#pragma once

#include <string>

#include "url.h"
#include "connection.h"

class Request {
    URL url;
    
    Connection* connect(URL);

    public:
        Request(URL);

        std::string send(const std::string);

        class RequestError : public std::exception {
            std::string message;

         public:
             RequestError(const std::string message) : message(message) {}
             char * what() {
                 return message.data();
             }

        };
};
