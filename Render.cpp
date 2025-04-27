#include <iostream>
#include <fstream>
#include <sstream>

#include "Render.h"
#include "HTTPResponse.h";

HTTPResponse Render(char request[512], std::string templateFilePath) {

    std::ifstream file(templateFilePath);
    std::ostringstream contentStream;
    contentStream << file.rdbuf();

    std::string header = "HTTP/1.0 200 OK";
    std::string ctype = "text/html";

    HTTPResponse res = HTTPResponse(header, ctype, contentStream.str());

    return res;

}