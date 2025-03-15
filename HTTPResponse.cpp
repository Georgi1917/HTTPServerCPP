#include <iostream>

class HTTPResponse {

    private:
        std::string HttpHeader;
        std::string contentType;
        std::string HtmlResponse;

    public:
        HTTPResponse(std::string header, std::string ctype, std::string htmlResponse) {

            HttpHeader = header;
            contentType = ctype;
            HtmlResponse = htmlResponse;

        }

        std::string GetResponse() {

            return HttpHeader + "\r\n" + contentType + "\r\n\n" + HtmlResponse;

        }

};