#include "Store.h"
#include <iostream>

int Store::nextId = 1;

Store::Store(std::string name, std::string location)
    : Node("S" + std::to_string(nextId++), name, location) {}

std::unordered_map<std::string, int> Store::getInventory() const {
    return inventory;
}

std::unordered_map<std::string, int> Store::getDemand() const {
    return demand;
}

bool Store::checkInventory(std::string product, int units) const {
    return inventory.count(product) && inventory.at(product) >= units;
}

bool Store::placeOrder(std::string warehouseId, std::string product, int units) {
    // For now just add to inventory
    // Later SupplyChainNetwork will handle talking to the actual Warehouse
    inventory[product] += units;
    return true;
}

void Store::display() const {
    std::cout << "Id: " << getId() << " | Name: " << getName() << " | Location: " << getLocation() << std::endl;
    std::cout << "Inventory:" << std::endl;
    for (const auto& item : inventory) {
        std::cout << "  " << item.first << ": " << item.second << std::endl;
    }
    std::cout << "Demand:" << std::endl;
    for (const auto& item : demand) {
        std::cout << "  " << item.first << ": " << item.second << std::endl;
    }
}

void Store::setDemand(std::string product, int units) {
    demand[product] += units;
}

Store::~Store() {

}



