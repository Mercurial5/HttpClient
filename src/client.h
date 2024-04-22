#pragma once

#include <string>
#include <sstream>
#include <map>

#include "url.h"
#include "request.h"
#include "connection.h"
#include "response.h"

class Client {
    public:
        static Response get(Request);

        class  ClientError: public std::exception {
            std::string message;

         public:
             ClientError(const std::string message) : message(message) {}
             char * what() {
                 return message.data();
             }

        };
};

