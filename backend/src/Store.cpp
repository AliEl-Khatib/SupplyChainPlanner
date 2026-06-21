#include "Store.h"
#include <iostream>
#include <Warehouse.h>

int Store::nextId = 1;

Store::Store(std::string name, std::string location)
    : Node("S" + std::to_string(nextId++), name, location) {}


std::unordered_map<std::string, int> Store::getDemand() const {
    return demand;
}

bool Store::checkInventory(std::string product, int units) const {
    std::unordered_map<std::string, int> inv = getInventory();
    return inv.count(product) && inv.at(product) >= units;
}

bool Store::placeOrder(std::string product, int units) {
    for (Node* neighbor : getNeighbors()) {
        Warehouse* warehouse = dynamic_cast<Warehouse*>(neighbor);
        if (warehouse != nullptr) {
            Message msg;
            msg.from = getId();
            msg.to = warehouse->getId();
            msg.product = product;
            msg.units = units;
            msg.type = "ORDER";
            warehouse->sendMessage(msg);
            return true;
        }
    }
    return false;
}

void Store::display() const {
    std::cout << "Id: " << getId() << " | Name: " << getName() << " | Location: " << getLocation() << std::endl;
    std::cout << "Inventory:" << std::endl;
    for (const auto& item : getInventory()) {
        std::cout << "  " << item.first << ": " << item.second << std::endl;
    }
    std::cout << "Demand:" << std::endl;
    for (const auto& item : demand) {
        std::cout << "  " << item.first << ": " << item.second << std::endl;
    }
}

void Store::simulate()
{
    while (getRunning()) {
        std::cout << "Store checking inventory" << std::endl;
        for (const auto& [product, units] : demand) {
            int inventoryUnits = getInventory()[product];
            if (inventoryUnits < units) {
                placeOrder(product, units - inventoryUnits);
                Message shipment = receiveMessage();
                if (!getRunning() && shipment.type.empty()) break;
                if (shipment.type == "SHIPMENT") {
                    addToInventory(shipment.product, shipment.units);
                }
            } else {
                takeFromInventory(product, units);
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void Store::setDemand(std::string product, int units) {
    demand[product] += units;
}

Store::~Store() {

}



