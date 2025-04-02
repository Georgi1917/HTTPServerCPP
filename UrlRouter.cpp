#include <iostream>
#include <vector>

class UrlNode {

    std::string url;
    void (*funcPtr)(char[512]);

    public:
        UrlNode (std::string requestUrl, void(*func)(char[512])) : url(requestUrl), funcPtr(func) {}

        void Execute(char value[512]) {

            funcPtr(value);

        }

};

class UrlRouter {

    private : 

        std::vector<UrlNode> routes;

    public :

        void AddRoute(std::string url, void(*func)(char[512])) {

            UrlNode node(url, func);

            routes.push_back(node);

        }

};