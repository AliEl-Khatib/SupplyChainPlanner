#ifndef SUPPLYCHAINNETWORK_H
#define SUPPLYCHAINNETWORK_H
#include "Node.h"
#include "Route.h"
#include <unordered_map>
#include <vector>

class SupplyChainNetwork {
private:
    std::unordered_map<std::string, Node*> nodes;
    std::unordered_map<std::string, Route*> routes;
        
public:
    SupplyChainNetwork();
    std::unordered_map<std::string, Node*> getNodes() const;
    void addNode(Node* node);
    void addRoute(Route* route);
    Node* findNode(std::string id) const;
    void display() const;
    std::vector<Route*> getRoutesFrom(std::string nodeId) const;
    ~SupplyChainNetwork();
};


#endif