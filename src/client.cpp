#include <string>
#include <sstream>

#include "client.h"
#include "request.h"
#include "url.h"
#include "connection.h"
#include "response.h"

Response Client::get(Request request) {
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
    
    std::stringstream response_stream;
    try {
        response_stream = connection->read();
    } catch (Connection::ConnectionError &e) {
        throw Client::ClientError(e.what());
    }
    
    return Response(response_stream);
}

