#include <iostream>

#include "../HTTPResponse.h"
#include "../Render.h"
#include "views.h"

HTTPResponse index(char request[512]) {

    return Render(request, "template/index.html");

}