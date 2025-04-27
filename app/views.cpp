#include <iostream>

#include "../HTTPResponse.h"
#include "../Render.h"

HTTPResponse index(char request[512]) {

    return Render(request, "template/index.html");

}