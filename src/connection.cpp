#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#include "connection.h"

Connection::Connection(const std::string host, const std::string port) {
    this->sfd = this->connect(host, port);
}

Connection::~Connection() {
    close(this->sfd);
}

void Connection::send(const std::string message) {
    int error = write(sfd, message.data(), message.size());
    if (error == -1) {
        throw Connection::ConnectionError("Failed to write: " + std::string(gai_strerror(errno)));
    }
    else if (error != message.size()) {
        throw Connection::ConnectionError("Partially failed to write: " + std::string(gai_strerror(errno)));
    }
}

std::string Connection::read() {
    shutdown(sfd, SHUT_WR);

    std::string response;
    while (true) {
        std::string response_chunk;
        response_chunk.resize(this->READ_CHUNK_SIZE);

        int error = ::read(sfd, &response_chunk[0], READ_CHUNK_SIZE);
        if (error == -1) {
            throw Connection::ConnectionError("Failed to read: " + std::string(gai_strerror(errno)));
        }

        response += response_chunk;

        if (error == 0) {
            break;
        }
    }

    return response;
}

addrinfo* Connection::get_addrinfo(const std::string host, const std::string port) {
    struct addrinfo hints;
    struct addrinfo* result;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    int error = getaddrinfo(host.data(), port.data(), &hints, &result);
    if (error != 0) {
        throw Connection::ConnectionError("Failed to fetch address info: " + std::string(gai_strerror(error)));
    }

    return result;
}

int Connection::connect(const std::string host, const std::string port) {
    struct addrinfo* result = this->get_addrinfo(host, port);	
    struct addrinfo* r = result;

    int sfd;
    bool connected = false;
    while (r) {
        // Here instead of result->... I could've used the constants such as AF_INET, SOCK_STREAM, 0.
        // But in documentation they decided to go with this more flexible way, so I stuck with it.
        sfd = socket(r->ai_family, r->ai_socktype, r->ai_protocol);
        if (sfd == -1) {
            freeaddrinfo(result);
            throw Connection::ConnectionError("Failed to open socket: " + std::string(gai_strerror(errno)));
        }

        int error = ::connect(sfd, r->ai_addr, r->ai_addrlen);
        if (error != -1) {
            connected = true;
            break;
        }

        close(sfd);

        r = r->ai_next;
    }

    freeaddrinfo(result);

    if (!connected) {
        throw ConnectionError("Failed to connect");
    }

    return sfd;
}
