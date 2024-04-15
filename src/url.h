#pragma once

#include <ostream>
#include <string>

class URL {
    public:
        struct Netloc {
            std::string host;
            std::string port;
        };

    private:
        class URLParser {
            public:
                static std::string scheme(std::string&);
                static URL::Netloc netloc(std::string&);
                static std::string fragment(std::string&);
                static std::string query(std::string&);
        };

        friend std::ostream& operator<<(std::ostream&, const URL&);
        std::string _scheme;
        struct URL::Netloc _netloc;
        std::string _fragment;
        std::string _query;
        std::string _path;

    public:

        explicit URL();
        explicit URL(const std::string&);

        void setUrl(std::string);

        std::string scheme() const;
        URL::Netloc netloc() const;
        std::string fragment() const;
        std::string query() const;
        std::string path() const;
        std::string full() const;
};
