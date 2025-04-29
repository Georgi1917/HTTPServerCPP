#include <iostream>
#include <vector>
#include "HTTPResponse.h"
#include "UrlRouter.h"

// class UrlNode {

//     std::string url;
//     HTTPResponse (*funcPtr)(char[512]);

//     public:
//         UrlNode (std::string requestUrl, HTTPResponse(*func)(char[512])) : url(requestUrl), funcPtr(func) {}

//         void Execute(char value[512]) {

//             funcPtr(value);

//         }

// };

// class UrlRouter {

//     private : 

//         std::vector<UrlNode> routes;

//     public :

//         void AddRoute(std::string url, HTTPResponse(*func)(char[512])) {

//             UrlNode node(url, func);

//             routes.push_back(node);

//         }

// };

UrlNode::UrlNode(std::string requestUrl, HTTPResponse(*func)(char[512])) : url(requestUrl), funcPtr(func) {}
void UrlNode::Execute(char value[512]) { funcPtr(value); }
std::string UrlNode::GetUrl() { return this->url; }

void UrlRouter::AddRoute(std::string url, HTTPResponse(*func)(char[512])) {

    UrlNode node(url, func);

    routes.push_back(node);

}

UrlNode UrlRouter::SearchForNode(std::string url) {

    for (int i = 0; i < routes.size(); i++) {

        UrlNode route = routes[i];

        if (route.GetUrl() == url) return route;

    }

}