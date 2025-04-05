#include <iostream>
#include <vector>

#include "HTTPResponse.cpp"

class UrlNode {

    std::string url;
    HTTPResponse (*funcPtr)(char[512]);

    public:
        UrlNode (std::string requestUrl, HTTPResponse(*func)(char[512])) : url(requestUrl), funcPtr(func) {}

        void Execute(char value[512]) {

            funcPtr(value);

        }

};

class UrlRouter {

    private : 

        std::vector<UrlNode> routes;

    public :

        void AddRoute(std::string url, HTTPResponse(*func)(char[512])) {

            UrlNode node(url, func);

            routes.push_back(node);

        }

};