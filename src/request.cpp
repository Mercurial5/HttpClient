#include <string>

#include "request.h"
#include "url.h"
#include "connection.h"

std::string Request::send(URL url) {
    Connection *connection; 
    try {
        connection = new Connection(url.netloc().host, url.netloc().port);
    } catch (Connection::ConnectionError &e) {
        throw Request::RequestError(e.what());
    }
    
    std::string message = Request::build_http_request_message(url);

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

std::string Request::build_http_request_message(URL url) {
    std::string message = "GET " + url.path() + " HTTP/1.1\n\n";
    message += "host: " + url.netloc().host;

    return message;
}
