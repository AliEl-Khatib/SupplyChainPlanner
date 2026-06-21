#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include "Node.h"
#include <unordered_map>

class Warehouse : public Node {
    private:
        static int nextId;
        int capacity;
        std::unordered_map<std::string, int> inventory;

    public:
        Warehouse(std::string name, int capacity, std::string location);
        int getCapacity() const;
        std::unordered_map<std::string, int> getInventory() const;
        bool requestFromFactory(std::string factoryId, std::string product, int units);
        std::pair<std::string, int> sendToStore(std::string storeId, std::string product, int units);
        virtual void display() const override;
        virtual ~Warehouse();
};


#endif