#include "Route.h"
#include <iostream>

int Route::nextId = 1;

Route::Route(Node* source, Node* destination, double cost, int capacity)
    : id("R" + std::to_string(nextId++)),
    source(source),
    destination(destination),
    cost(cost),
    capacity(capacity) {}

Node* Route::getSource() const{
    return source;
}

Node* Route::getDestination() const{
    return destination;
}

double Route::getCost() const{
    return cost;
}

std::string Route::getId() const{
    return id;
}

int Route::getCapacity() const{
    return capacity;
}

void Route::display() const {
    std::cout << "Id: " << id << " | Cost: " << cost << " | Capacity: " << capacity << std::endl;
    std::cout << "Source: " << getSource()->getLocation() << " -> Destination: " << getDestination()->getLocation() << std::endl;
}

Route::~Route(){

}

