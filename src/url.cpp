#include <string>

#include "url.h"

URL::URL() {}

URL::URL(const std::string& url) {
    this->setUrl(url);
}

void URL::setUrl(std::string url) {
    this->_scheme = URLParser::scheme(url);
    this->_netloc = URLParser::netloc(url);
    this->_fragment = URLParser::fragment(url);
    this->_query = URLParser::query(url);
    this->_path = url == "" ? "/" : url;
}


std::string URL::scheme() const {
    return this->_scheme;
}

URL::Netloc URL::netloc() const {
    return this->_netloc;
}

std::string URL::fragment() const {
    return this->_fragment;
}

std::string URL::query() const {
    return this->_query;
}

std::string URL::path() const {
    return this->_path;
}

std::string URL::full() const {
    std::string url = this->_scheme + "://";
    url += this->_netloc.host;
    if (!this->_netloc.port.empty()) {
        url += ":" + this->_netloc.port;
    }
    url += this->_path;

    if (!this->_query.empty()) url += "?" + this->_query;
    if (!this->_fragment.empty()) url += "#" + this->_fragment;

    return url;
}

std::string URL::URLParser::scheme(std::string& url) {
    size_t i = url.find(':');
    std::string scheme = url.substr(0, i);
    url = url.substr(i + 3);

    return scheme;
}

URL::Netloc URL::URLParser::netloc(std::string& url) {
    size_t closest_delimiter = url.size();
    for (const char& c : "/?#") {
        size_t delimiter = url.find(c);
        if (url.find(c) != std::string::npos) {
            closest_delimiter = std::min(closest_delimiter, delimiter);
        }
    }

    std::string host = url.substr(0, closest_delimiter);
    url = url.substr(closest_delimiter);

    int index = host.find(':');
    if (index == std::string::npos) {
        return URL::Netloc{host};
    }

    std::string port = host.substr(index + 1, closest_delimiter);
    host = host.substr(0, closest_delimiter - port.size() - 1);

    return URL::Netloc{host, port};
}

std::string URL::URLParser::fragment(std::string& url) {
    size_t i = url.find('#');
    if (i == std::string::npos) {
        return {};
    }

    std::string fragment = url.substr(i + 1);
    url = url.substr(0, i);

    return fragment;
}

std::string URL::URLParser::query(std::string& url) {
    size_t i = url.find('?');
    if (i == std::string::npos) {
        return {};
    }

    std::string query = url.substr(i + 1);
    url = url.substr(0, i);

    return query;
}

std::ostream& operator<<(std::ostream& out, const URL& url) {
    return out << url.full();
}
