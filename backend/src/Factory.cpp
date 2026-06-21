#include "Factory.h"
#include <iostream>
#include <chrono>
#include <thread>


int Factory::nextId = 1;

Factory::Factory(std::string name, std::string location, int capacity, double productionRate)
    : Node("F" + std::to_string(nextId++), name, location), capacity(capacity), productionRate(productionRate) {}


int Factory::getCapacity() const {
    return capacity;
}

double Factory::getProductionRate() const {
    return productionRate;
}

void Factory::display() const {
    std::cout << "Id: " << getId() << " | Name: " << getName() << " | Location: " << getLocation() << " | Capacity: " << capacity << " | ProductionRate: " << productionRate << std::endl;
    std::cout << "Inventory:" << std::endl;
    for (const auto& item : getInventory()) {
        std::cout << "  " << item.first << ": " << item.second << std::endl;
    }
}

void Factory::simulate()
{
    while (getRunning()) {
        std::cout << "Factory producing widgets" << std::endl;
        produce("widgets", 10);
        Message msg;
        msg.from = getId();
        msg.product = "widgets";
        msg.units = 10;
        msg.type = "PRODUCE";
        for (Node* neighbor : getNeighbors()) {
            msg.to = neighbor->getId();
            neighbor->sendMessage(msg);
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void Factory::produce(std::string product, int units) {
    addToInventory(product, units); 
}

Factory::~Factory(){
    
}


