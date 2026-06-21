#ifndef FACTORY_H
#define FACTORY_H
#include <unordered_map>
#include "Node.h"

class Factory : public Node{
    private:
        static int nextId;
        int capacity;
        double productionRate;
        
    public:
        Factory(std::string name, std::string location, int capacity, double productionRate);

        int getCapacity() const;
        double getProductionRate() const;
        virtual void display() const override;
        virtual void simulate() override;
        void produce(std::string product, int units);
        virtual ~Factory();
};

#endif