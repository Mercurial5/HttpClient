#include <algorithm>
#include <string>
#include <map>

#include "request.h"
#include "url.h"


Request::Request(URL url) : _url(url) {}

Request::Request(URL url, std::map<std::string, std::string> headers) : _url(url), _headers(headers) {
    std::map<std::string, std::string> default_headers = {
        {"user-agent", "cpp-http-client"}
    };

    this->update_headers(default_headers);
}

URL Request::url() {
    return this->_url;
}

void Request::update_headers(std::map<std::string, std::string> headers) {
    for (auto header: headers) {
        std::string lower_header;
        std::transform(begin(header.first), end(header.first), begin(lower_header), [](const char c) { return std::tolower(c); });
        if (this->_headers.find(lower_header) == end(this->_headers)) {
            this->_headers[lower_header] = header.second; 
        }
    }
}

std::map<std::string, std::string> Request::headers() {
    return this->_headers;
}

std::string Request::http() {
    this->_headers["host"] = this->_url.netloc().host;

    std::string message = "GET " + this->_url.path() + " HTTP/1.1\n";

    for (auto header: this->_headers) {
        message += header.first + ": " + header.second + "\n";
    }

    message += "\n";
    return message;

}
