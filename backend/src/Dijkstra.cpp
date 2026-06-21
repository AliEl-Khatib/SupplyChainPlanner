#include "Dijkstra.h"
#include <iostream>
#include <limits>

Dijkstra::Dijkstra() {}

void Dijkstra::run(SupplyChainNetwork& network, std::string sourceId) {

    dist.clear();
    prev.clear();
    while (!pq.empty()) pq.pop();

    // Get all nodes and set distance to infinity
    for (const auto& pair : network.getNodes()) {
        dist[pair.first] = std::numeric_limits<double>::infinity();
    }

    // Source node distance is 0
    dist[sourceId] = 0.0;
    pq.push({0.0, sourceId});

    while (!pq.empty()) {
        auto [cost, nodeId] = pq.top();
        pq.pop();

        // Skip if we already found a shorter path
        if (cost > dist[nodeId]) continue;

        // Explore neighbors
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

    // Print results
    std::cout << "Shortest paths from " << sourceId << ":" << std::endl;
    for (const auto& pair : dist) {
        std::cout << sourceId << " -> " << pair.first << " : " << pair.second << std::endl;
    }
}

Dijkstra::~Dijkstra() {}