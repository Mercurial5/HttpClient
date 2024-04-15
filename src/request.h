#pragma once

#include <string>

#include "url.h"
#include "connection.h"

class Request {
    static std::string build_http_request_message(URL);

    public:
        static std::string send(URL);

        class RequestError : public std::exception {
            std::string message;

         public:
             RequestError(const std::string message) : message(message) {}
             char * what() {
                 return message.data();
             }

        };
};
