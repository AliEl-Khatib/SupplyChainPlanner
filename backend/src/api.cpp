#include "crow/crow_all.h"
#include "json.hpp"
#include "Factory.h"
#include "Warehouse.h"
#include "Store.h"
#include "SupplyChainNetwork.h"
#include "Dijkstra.h"

using json = nlohmann::json;

void startAPI(SupplyChainNetwork& network) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/network")
    ([&network]() {
        json result;
        result["nodes"] = json::array();
        result["routes"] = json::array();

        for (const auto& pair : network.getNodes()) {
            json node;
            node["id"] = pair.second->getId();
            node["name"] = pair.second->getName();
            node["location"] = pair.second->getLocation();
            result["nodes"].push_back(node);
        }

        for (const auto& pair : network.getRoutes()) {
            json route;
            route["id"] = pair.second->getId();
            route["from"] = pair.second->getSource()->getId();
            route["to"] = pair.second->getDestination()->getId();
            route["cost"] = pair.second->getCost();
            result["routes"].push_back(route);
        }

        return crow::response(200, result.dump());
    });

    CROW_ROUTE(app, "/state")
    ([&network]() {
        json result;
        result["nodes"] = json::array();

        for (const auto& pair : network.getNodes()) {
            json node;
            node["id"] = pair.second->getId();
            node["name"] = pair.second->getName();
            node["inventory"] = pair.second->getInventory();
            result["nodes"].push_back(node);
        }

        return crow::response(200, result.dump());
    });

    CROW_ROUTE(app, "/dijkstra/<string>")
    ([&network](std::string sourceId) {
        Dijkstra dijkstra;
        json result = dijkstra.runAndReturn(network, sourceId);
        return crow::response(200, result.dump());
    });

    CROW_ROUTE(app, "/simulate/start").methods("POST"_method)
    ([&network]() {
        try {
            for (const auto& pair : network.getNodes()) {
                if (!pair.second->getRunning()) {
                    pair.second->startSimulation();
                }
            }
            return crow::response(200, "{\"status\": \"simulation started\"}");
        } catch (const std::exception& e) {
            return crow::response(500, e.what());
        }
    });

    CROW_ROUTE(app, "/simulate/stop").methods("POST"_method)
    ([&network]() {
        try {
            for (const auto& pair : network.getNodes()) {
                if (pair.second->getRunning()) {
                    pair.second->stopSimulation();
                }
            }
            return crow::response(200, "{\"status\": \"simulation stopped\"}");
        } catch (const std::exception& e) {
            return crow::response(500, e.what());
        }
        
    });

    app.port(8080).multithreaded().run();
}