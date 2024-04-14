# HttpClient

HttpClient allows you easily make an http requests.

## Current feautres

- Connect to a server by `host` and `port`.
- Send/receive messages to/from server.

## Examples

### Connect to a server

```cpp
#include <iostream>
#include <string>

#include "connection.h"

int main() {
	std::string host = "google.com";
	std::string port = "80";

	Connection* connection;	
	try {
		connection = new Connection(host, port);
	} catch (Connection::ConnectionError &e) {
		std::cout << e.what() << std::endl;
		return 0;
	}
    
    std::cout << "Succesfully connected to the server!" << std::endl;
}
```

### Send message

```cpp
std::string message = "GET / HTTP/1.1\n\nhost: google.com";

try {
    connection->send(message);
} catch (Connection::ConnectionError &e) {
    std::cout << e.what() << std::endl;
    return 0;
}
```

### Receive message

```cpp
try {
    std::string response = connection->read();
} catch (Connection::ConnectionError &e) {
    std::cout << e.what() << std::endl;
    return 0;
}

std::cout << response << std::endl;
```
