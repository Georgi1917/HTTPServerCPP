#include "../UrlRouter.h"
#include "views.h"
#include "urls.h"
#include <iostream>

UrlRouter router = UrlRouter();

void AddingRoutes() {

    router.AddRoute("", index);
    router.AddRoute("about", about);
    std::cout << "Abra Kadabra!!!" << std::endl;

}