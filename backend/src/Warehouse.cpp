#include "Warehouse.h"
#include <iostream>
int Warehouse::nextId = 1;

Warehouse::Warehouse(std::string name, int capacity, std::string location)
    : Node("W" + std::to_string(nextId++), name, location), capacity(capacity) {}

int Warehouse::getCapacity() const {
    return capacity;
}

std::unordered_map<std::string, int> Warehouse::getInventory() const {
    return inventory;
}

bool Warehouse::requestFromFactory(std::string factoryId, std::string product, int units) {
    inventory[product] += units;
    return true;
}

std::pair<std::string, int> Warehouse::sendToStore(std::string storeId, std::string product, int units) {
    if (inventory[product] >= units){
        inventory[product] -= units;
        return {product, units};
    }

    return {product, 0};
}

void Warehouse::display() const {
    std::cout << "Id: " << getId() << " | Name: " << getName() << " | Location: " << getLocation() << " | Capacity: " << capacity << std::endl;
    std::cout << "Inventory: " << std::endl;
    for (const auto& item : inventory) {
        std::cout << "  " << item.first << ": " << item.second << std::endl;
    }
}

Warehouse::~Warehouse(){
    
}



