#include <iostream>

#include "../HTTPResponse.h"
#include "../Render.h"
#include "views.h"

HTTPResponse index(char request[512]) {

    return Render(request, "templates/index.html");

}

HTTPResponse about(char request[512]) {

    return Render(request, "templates/about.html");

}