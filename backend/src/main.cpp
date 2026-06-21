#include "Node.h"
#include "Factory.h"
#include "Warehouse.h"
#include "Store.h"
#include "Route.h"
#include "SupplyChainNetwork.h"
#include "Dijkstra.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    // Create nodes
    Factory f1("Factory A", "Ottawa", 100, 10.5);
    Warehouse w1("Warehouse A", 500, "Toronto");
    Store s1("Store A", "Vancouver");

    // Set up neighbors
    f1.addNeighbor(&w1);   // factory sends to warehouse
    w1.addNeighbor(&f1);   // warehouse can request from factory
    w1.addNeighbor(&s1);   // warehouse sends to store
    s1.addNeighbor(&w1);   // store orders from warehouse

    // Set store demand
    s1.setDemand("widgets", 20);

    // Create routes
    Route r1(&f1, &w1, 100.0, 200);
    Route r2(&w1, &s1, 50.0, 100);

    // Build network
    SupplyChainNetwork network;
    network.addNode(&f1);
    network.addNode(&w1);
    network.addNode(&s1);
    network.addRoute(&r1);
    network.addRoute(&r2);

    // Run Dijkstra
    std::cout << "\n=== Dijkstra from F1 ===" << std::endl;
    Dijkstra dijkstra;
    dijkstra.run(network, "F1");

    // Start simulation
    std::cout << "\n=== Starting Simulation ===" << std::endl;
    f1.startSimulation();
    w1.startSimulation();
    s1.startSimulation();

    // Let it run for 20 seconds
    std::this_thread::sleep_for(std::chrono::seconds(20));

    // Stop simulation
    std::cout << "\n=== Stopping Simulation ===" << std::endl;
    // Stop in reverse dependency order
    s1.stopSimulation();
    w1.stopSimulation();
    f1.stopSimulation(); 
    // Print final state
    std::cout << "\n=== Final State ===" << std::endl;
    f1.display();
    w1.display();
    s1.display();

    return 0;
}