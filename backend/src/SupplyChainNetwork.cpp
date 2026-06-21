#include "SupplyChainNetwork.h"
#include <iostream>
SupplyChainNetwork::SupplyChainNetwork() {

}

void SupplyChainNetwork::addNode(Node* node) {
    std::string id = node->getId();
    nodes[id] = node;
}

void SupplyChainNetwork::addRoute(Route* route) {
    std::string id = route->getId();
    routes[id] = route;
}

Node* SupplyChainNetwork::findNode(std::string id) const{
    auto result = nodes.find(id);
    if (result != nodes.end()){
        return result->second;
    }
    return nullptr;
}

std::unordered_map<std::string, Node*> SupplyChainNetwork::getNodes() const{
    return nodes;
}

std::unordered_map<std::string, Route *> SupplyChainNetwork::getRoutes() const
{
    return routes;
}

void SupplyChainNetwork::display() const{
    std::cout << "Nodes: " << std::endl;
    for (const auto& node : nodes) {
        node.second->display();
    }
    std::cout << "Routes: " << std::endl;
    for (const auto& route : routes) {
        route.second->display();
    }
}

std::vector<Route*> SupplyChainNetwork::getRoutesFrom(std::string nodeId) const {
    std::vector<Route*> rts;
    for (const auto& routeInfo : routes) {
        Route* route = routeInfo.second;
        if (route->getSource()->getId() == nodeId) {
            rts.push_back(route);
        }
    }

    return rts;
}

SupplyChainNetwork::~SupplyChainNetwork() {

}