#ifndef STORE_H
#define STORE_H
#include "Node.h"
#include <unordered_map>

class Store : public Node {
private:
    static int nextId;
    std::unordered_map<std::string, int> inventory;
    std::unordered_map<std::string, int> demand;
public:
    Store(std::string name, std::string location);
    
    std::unordered_map<std::string, int> getInventory() const;
    std::unordered_map<std::string, int> getDemand() const;
    bool checkInventory(std::string product, int units) const;
    bool placeOrder(std::string product, int units);
    void setDemand(std::string product, int units);

    virtual void display() const override;
    virtual void simulate() override;
    virtual ~Store();
    
        
    
};


#endif