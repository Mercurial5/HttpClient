#pragma once

#include <string>
#include <map>

#include "url.h"
#include "connection.h"

class Client {
    static std::string build_http_request_message(URL, std::map<std::string, std::string>);
    
    static std::map<std::string, std::string> DEFAULT_HEADERS;
    public:
        static std::string send(URL, std::map<std::string, std::string> = std::map<std::string, std::string>());

        class  ClientError: public std::exception {
            std::string message;

         public:
             ClientError(const std::string message) : message(message) {}
             char * what() {
                 return message.data();
             }

        };
};

