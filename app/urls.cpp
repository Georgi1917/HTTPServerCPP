#include "../UrlRouter.h"
#include "views.h"
#include "urls.h"
#include <iostream>

UrlRouter router = UrlRouter();

void AddingRoutes() {

    router.AddRoute(" ", index);
    std::cout << "Abra kadabra" << std::endl;

}