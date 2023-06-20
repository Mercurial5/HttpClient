#include <string>

#include "url.h"

URL::URL() {}

URL::URL(const std::string& url) {
    this->setUrl(url);
}

void URL::setUrl(std::string url) {
    this->scheme = URLParser::scheme(url);
    this->netloc = URLParser::netloc(url);
    this->fragment = URLParser::fragment(url);
    this->query = URLParser::query(url);
    this->path = url;
}

std::string URL::full() const {
    std::string url = this->scheme + "://" + this->netloc + this->path;

    if (!this->query.empty()) url += "?" + this->query;
    if (!this->fragment.empty()) url += "#" + this->fragment;

    return url;
}

std::string URL::URLParser::scheme(std::string& url) {
    size_t i = url.find(':');
    std::string scheme = url.substr(0, i);
    url = url.substr(i + 3);

    return scheme;
}

std::string URL::URLParser::netloc(std::string& url) {
    size_t closest_delimiter = url.size();
    for (const char& c : "/?#") {
        size_t delimiter = url.find(c);
        if (url.find(c) != std::string::npos) {
            closest_delimiter = std::min(closest_delimiter, delimiter);
        }
    }

    std::string netloc = url.substr(0, closest_delimiter);
    url = url.substr(closest_delimiter);

    return netloc;
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
