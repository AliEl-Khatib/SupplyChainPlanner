#include "Node.h"
#include "Factory.h"
#include "Warehouse.h"
#include "Store.h"
#include "Route.h"
#include "SupplyChainNetwork.h"
#include "Dijkstra.h"
#include <iostream>

int main() {
    // Create nodes
    Factory f1("Factory A", "Ottawa", 100, 10.5);
    Factory f2("Factory B", "Montreal", 200, 20.0);
    Warehouse w1("Warehouse A", 500, "Toronto");
    Store s1("Store A", "Vancouver");
    Store s2("Store B", "Calgary");

    // Create routes
    Route r1(&f1, &w1, 100.0, 200);
    Route r2(&f2, &w1, 80.0, 300);
    Route r3(&w1, &s1, 50.0, 100);
    Route r4(&w1, &s2, 60.0, 150);

    // Build network
    SupplyChainNetwork network;
    network.addNode(&f1);
    network.addNode(&f2);
    network.addNode(&w1);
    network.addNode(&s1);
    network.addNode(&s2);
    network.addRoute(&r1);
    network.addRoute(&r2);
    network.addRoute(&r3);
    network.addRoute(&r4);

    // Run Dijkstra from F1
    std::cout << "\n=== Dijkstra from F1 ===" << std::endl;
    Dijkstra dijkstra;
    dijkstra.run(network, "F1");

    // Run Dijkstra from F2
    std::cout << "\n=== Dijkstra from F2 ===" << std::endl;
    Dijkstra dijkstra2;
    dijkstra2.run(network, "F2");

    return 0;
}