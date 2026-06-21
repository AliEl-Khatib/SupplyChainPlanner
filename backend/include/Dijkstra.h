#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <unordered_map>
#include "Algorithm.h"
#include <string>
#include <queue>

class Dijkstra : public Algorithm {
    private:
        std::unordered_map<std::string, double> dist;
        std::unordered_map<std::string, std::string> prev;
        std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<std::pair<double, std::string>>> pq;
    public:
        Dijkstra();
        virtual void run(SupplyChainNetwork& network, std::string sourceId) override;
        ~Dijkstra();
};

#endif