#include <string>
#include <sstream>

#include "client.h"
#include "request.h"
#include "url.h"
#include "connection.h"

std::stringstream Client::send(Request request) {
    Connection *connection; 
    try {
        connection = new Connection(request.url().netloc().host, request.url().netloc().port);
    } catch (Connection::ConnectionError &e) {
        throw Client::ClientError(e.what());
    }
    
    try {
        connection->send(request.http());
    } catch (Connection::ConnectionError &e) {
        throw Client::ClientError(e.what());
    }

    try {
        return connection->read();
    } catch (Connection::ConnectionError &e) {
        throw Client::ClientError(e.what());
    }
}

