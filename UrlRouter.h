#include <iostream>
#include <vector>
#include "HTTPResponse.h"

#pragma once

class UrlNode {

    std::string url;
    HTTPResponse (*funcPtr)(char[512]);

    public:
        UrlNode(std::string requestUrl, HTTPResponse(*func)(char[512]));

        void Execute(char value[512]);

};

class UrlRouter {

    private:

        std::vector<UrlNode> routes;

    public:

        void AddRoute(std::string url, HTTPResponse(*func)(char[512]));

};