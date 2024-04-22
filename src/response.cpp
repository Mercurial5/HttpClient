#include <string>
#include <sstream>
#include <map>

#include "response.h"
#include "utils.h"

Response::Response(std::stringstream& response) {
    // read first line
    std::string first_line;
    getline(response, first_line);

    std::vector<std::string> header_result = split(first_line, " ");
    if (header_result.size() != 3) {
        throw std::invalid_argument("Header size is not 3");
    }

    this->status_code = stoi(header_result[1]);

    // read headers     
    std::string header_str;
    while (true) {
        getline(response, header_str);
        if (is_empty(header_str)) {
            break;
        }

        std::vector<std::string> header = split(header_str, ": ");
        headers[header[0]] = header[1];
    }
    
    std::string body_line;
    while (getline(response, body_line)) {
        this->body += body_line;
    }
}
