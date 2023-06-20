#pragma once

#include <ostream>
#include <string>

class URL {
    class URLParser {
    public:
        static std::string scheme(std::string&);
        static std::string netloc(std::string&);
        static std::string fragment(std::string&);
        static std::string query(std::string&);
    };

    friend std::ostream& operator<<(std::ostream&, const URL&);
public:
    std::string scheme;
    std::string netloc;
    std::string fragment;
    std::string query;
    std::string path;

    explicit URL();
    explicit URL(const std::string&);

    void setUrl(std::string);

    std::string full() const;
};
