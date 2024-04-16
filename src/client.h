#pragma once

#include <string>
#include <map>

#include "url.h"
#include "request.h"
#include "connection.h"

class Client {
    public:
        static std::string send(Request);

        class  ClientError: public std::exception {
            std::string message;

         public:
             ClientError(const std::string message) : message(message) {}
             char * what() {
                 return message.data();
             }

        };
};

