#include "Parser.h"

HttpHeaderParser::HttpHeaderParser(const std::string& rawHttpData) : rawHttpData_(rawHttpData) {
    parseHeaders(rawHttpData);
}

int HttpHeaderParser::getContentLength() const {
    return contentLength_;
}

void HttpHeaderParser::parseHeaders(const std::string& rawHttpData) {
    size_t pos = 0;
    size_t prevPos = 0;
    bool foundContentLength = false;

    while ((pos = rawHttpData_.find("\r\n", prevPos)) != std::string::npos) {
        std::string line = rawHttpData_.substr(prevPos, pos - prevPos);
        prevPos = pos + 2;

        if (line.empty()) {
            // Reached the end of headers
            break;
        }

        if (!foundContentLength && line.find("Content-Length:") == 0) {
            // Found Content-Length header
            foundContentLength = true;
            contentLength_ = std::stoi(line.substr(15));
        }
    }
}