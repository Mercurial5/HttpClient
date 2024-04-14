#include <netdb.h>
#include <string>

class Connection {
    int READ_CHUNK_SIZE = 1024;
    int sfd;

    addrinfo* get_addrinfo(const std::string host, const std::string port);
    int connect(const std::string host, const std::string port);

    public:
    Connection(const std::string host, const std::string port);

    void send(const std::string message);
    std::string read();

    class ConnectionError : public std::exception {
        std::string message;

        public:
        ConnectionError(const std::string message) : message(message) {}
        char * what() {
            return message.data();
        }
    };
};
