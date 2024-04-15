#include <string>

#include "request.h"
#include "url.h"
#include "connection.h"

Request::Request(URL url) : url(url) {};

std::string Request::send(const std::string message) {
    Connection *connection; 
    try {
        connection = new Connection(url.netloc().host, url.netloc().port);
    } catch (Connection::ConnectionError &e) {
        throw Request::RequestError(e.what());
    }

    try {
        connection->send(message);
    } catch (Connection::ConnectionError &e) {
        throw Request::RequestError(e.what());
    }

    try {
        return connection->read();
    } catch (Connection::ConnectionError &e) {
        throw Request::RequestError(e.what());
    }
}

Connection* Request::connect(URL url) {
    try {
        return new Connection(url.netloc().host, url.netloc().port);
    } catch (Connection::ConnectionError &e) {
        throw Request::RequestError(e.what());
    }
}
