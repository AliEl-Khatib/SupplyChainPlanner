#include "Warehouse.h"
#include <iostream>
#include <Factory.h>
#include <Store.h>
int Warehouse::nextId = 1;

Warehouse::Warehouse(std::string name, int capacity, std::string location)
    : Node("W" + std::to_string(nextId++), name, location), capacity(capacity) {}

int Warehouse::getCapacity() const
{
    return capacity;
}

std::unordered_map<std::string, int> Warehouse::getInventory() const
{
    return inventory;
}

bool Warehouse::requestFromFactory(std::string id, std::string product, int units)
{
    inventory[product] += units;
    return true;
}

void Warehouse::simulate()
{
    while (getRunning())
    {
        Message msg = receiveMessage();
        if (!getRunning() && msg.type.empty()) break;
        std::cout << "Warehouse received message: " << msg.type << std::endl;
        if (msg.type == "PRODUCE")
        {
            inventory[msg.product] += msg.units;
            std::cout << "Warehouse inventory after PRODUCE: " << inventory[msg.product] << std::endl;
        }
        else if (msg.type == "ORDER")
        {
            std::cout << "Warehouse inventory before ORDER: " << inventory[msg.product] << std::endl;
            auto result = sendToStore(msg.from, msg.product, msg.units);
            std::cout << "Shipment sent: " << result.first << " x" << result.second << std::endl;
            for (Node *neighbor : getNeighbors())
            {
                if (neighbor->getId() == msg.from)
                {
                    Message shipment;
                    shipment.from = getId();
                    shipment.to = msg.from;
                    shipment.product = result.first;
                    shipment.units = result.second;
                    shipment.type = "SHIPMENT";
                    neighbor->sendMessage(shipment);
                    break;
                }
            }
        }
    }
}

std::pair<std::string, int> Warehouse::sendToStore(std::string storeId, std::string product, int units) {
    int available = inventory[product];
    if (available > 0) {
        int toSend = std::min(units, available);
        inventory[product] -= toSend;
        return {product, toSend};
    }
    return {product, 0};
}

void Warehouse::display() const
{
    std::cout << "Id: " << getId() << " | Name: " << getName() << " | Location: " << getLocation() << " | Capacity: " << capacity << std::endl;
    std::cout << "Inventory: " << std::endl;
    for (const auto &item : inventory)
    {
        std::cout << "  " << item.first << ": " << item.second << std::endl;
    }
}

Warehouse::~Warehouse()
{
}
