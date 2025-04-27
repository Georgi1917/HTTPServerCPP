#include <iostream>

#pragma once

class HTTPResponse {

    private:
        std::string HttpHeader;
        std::string contentType;
        std::string HtmlResponse;

    public:

        HTTPResponse(std::string header, std::string ctype, std::string htmlResponse);

        std::string GetResponse();

};