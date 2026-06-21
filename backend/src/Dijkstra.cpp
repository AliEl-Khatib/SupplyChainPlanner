#include "Dijkstra.h"
#include <iostream>
#include <limits>

Dijkstra::Dijkstra() {}


nlohmann::json Dijkstra::runAndReturn(SupplyChainNetwork& network, std::string sourceId) {
    dist.clear();
    prev.clear();
    while (!pq.empty()) pq.pop();

    for (const auto& pair : network.getNodes()) {
        dist[pair.first] = std::numeric_limits<double>::infinity();
    }

    dist[sourceId] = 0.0;
    pq.push({0.0, sourceId});

    while (!pq.empty()) {
        auto [cost, nodeId] = pq.top();
        pq.pop();

        if (cost > dist[nodeId]) continue;

        for (Route* route : network.getRoutesFrom(nodeId)) {
            std::string neighborId = route->getDestination()->getId();
            double newCost = dist[nodeId] + route->getCost();
            if (newCost < dist[neighborId]) {
                dist[neighborId] = newCost;
                prev[neighborId] = nodeId;
                pq.push({newCost, neighborId});
            }
        }
    }

    nlohmann::json result;
    result["source"] = sourceId;
    result["paths"] = nlohmann::json::array();

    for (const auto& pair : dist) {
        nlohmann::json path;
        path["to"] = pair.first;
        path["cost"] = pair.second == std::numeric_limits<double>::infinity() ? -1 : pair.second;
        path["path"] = getPath(pair.first);
        result["paths"].push_back(path);
    }

    return result;
}

void Dijkstra::run(SupplyChainNetwork& network, std::string sourceId) {
    nlohmann::json result = runAndReturn(network, sourceId);
    std::cout << result.dump(4) << std::endl;
}

std::vector<std::string> Dijkstra::getPath(std::string destId) {
    std::vector<std::string> path;
    std::string current = destId;
    
    while (prev.count(current)) {
        path.push_back(current);
        current = prev[current];
    }
    path.push_back(current);
    
    std::reverse(path.begin(), path.end());
    return path;
}

Dijkstra::~Dijkstra() {}