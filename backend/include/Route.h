#ifndef ROUTE_H
#define ROUTE_H
#include "Node.h"

class Route
{
private:
    static int nextId;
    std::string id;
    Node* source;
    Node* destination;
    double cost;
    int capacity;
public:
    Route(Node* source, Node* destination, double cost, int capacity);
    Node* getSource() const;
    Node* getDestination() const;
    double getCost() const;
    int getCapacity() const;
    std::string getId() const;
    void display() const;

    ~Route();
};

#endif
