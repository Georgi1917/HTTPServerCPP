#include <iostream>
#include <fstream>
#include <sstream>

#include "HTTPResponse.cpp";

HTTPResponse Render(char request[512], std::string templateFilePath) {

    std::ifstream file(templateFilePath);
    std::ostringstream contentStream;
    contentStream << file.rdbuf();

    std::string header = "HTTP/1.0 200 OK";
    std::string ctype = "text/html";

    HTTPResponse res = HTTPResponse(header, ctype, contentStream.str());

    return res;

}