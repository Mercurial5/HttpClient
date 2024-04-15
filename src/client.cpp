#include <string>
#include <map>

#include "client.h"
#include "url.h"
#include "connection.h"

std::map<std::string, std::string> Client::DEFAULT_HEADERS = {
    {"User-Agent", "cpp-http-client"},
};


std::string Client::send(URL url, std::map<std::string, std::string> headers) {
    Connection *connection; 
    try {
        connection = new Connection(url.netloc().host, url.netloc().port);
    } catch (Connection::ConnectionError &e) {
        throw Client::ClientError(e.what());
    }
    
    std::string message = Client::build_http_request_message(url, headers);

    try {
        connection->send(message);
    } catch (Connection::ConnectionError &e) {
        throw Client::ClientError(e.what());
    }

    try {
        return connection->read();
    } catch (Connection::ConnectionError &e) {
        throw Client::ClientError(e.what());
    }
}

std::string Client::build_http_request_message(URL url, std::map<std::string, std::string> headers) {
    headers.merge(Client::DEFAULT_HEADERS);

    std::string message = "GET " + url.path() + " HTTP/1.1\n";
    message += "Host: " + url.netloc().host + "\n";

    for (auto header: headers) {
        message += header.first + ": " + header.second + "\n";
    }

    return message;
}
