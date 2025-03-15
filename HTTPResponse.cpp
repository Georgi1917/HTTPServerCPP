#include <iostream>

class HTTPResponse {

    private:
        std::string HttpHeader;
        std::string contentType;
        std::string HtmlResponse;

    public:
        HTTPResponse(std::string htmlResponse) {

            HttpHeader = "HTTP/1.0 200 OK\r\n";
            contentType = "Content-type: text/html\r\n\n";

            HtmlResponse = HttpHeader + contentType + htmlResponse;

        }

        std::string GetResponse() {

            return HtmlResponse;

        }

};