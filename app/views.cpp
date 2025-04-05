#include <iostream>

#include "../HTTPResponse.cpp"
#include "../Render.cpp"

HTTPResponse index(char request[512]) {

    return Render(request, "template/index.html");

}