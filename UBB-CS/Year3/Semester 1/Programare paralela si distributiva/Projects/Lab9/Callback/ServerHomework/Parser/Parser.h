#ifndef SERVERHOMEWORK_PARSER_H
#define SERVERHOMEWORK_PARSER_H

#include <string>

class HttpHeaderParser {
public:
    HttpHeaderParser(const std::string& rawHttpData);

    int getContentLength() const;

private:
    void parseHeaders(const std::string& rawHttpData);

    std::string rawHttpData_;
    int contentLength_ = -1;
};

#endif // SERVERHOMEWORK_PARSER_H
