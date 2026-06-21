#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include "Node.h"
#include <unordered_map>

class Warehouse : public Node {
    private:
        static int nextId;
        int capacity;

    public:
        Warehouse(std::string name, int capacity, std::string location);
        int getCapacity() const;
        bool requestFromFactory(std::string id, std::string product, int units);
        std::pair<std::string, int> sendToStore(std::string storeId, std::string product, int units);
        virtual void display() const override;
        virtual void simulate() override;
        virtual ~Warehouse();
};


#endif