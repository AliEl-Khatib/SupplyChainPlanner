#include "Node.h"
#include <iostream>

Node::Node(std::string id, std::string name, std::string location) {
    this->id = id;
    this->name = name;
    this->location = location;
}

std::string Node::getId() const {
    return id;
}

std::string Node::getName() const {
    return name;
}

std::string Node::getLocation() const {
    return location;
}

std::vector<Node *> Node::getNeighbors() const
{
    return neighbors;
}

bool Node::getRunning() const
{
    return running;
}

void Node::display() const {
    std::cout << "Id: " << id << "Name: " << name << "Location: " << location << std::endl;
}

void Node::sendMessage(Message msg) {
    std::unique_lock<std::mutex> lock(mtx);
    inbox.push(msg);
    cv.notify_one();
}

Message Node::receiveMessage() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] { return !inbox.empty() || !running; });
    if (!running) return Message{};
    Message msg = inbox.front();
    inbox.pop();
    return msg;
}

void Node::addNeighbor(Node* neighbor) {
    neighbors.push_back(neighbor);
}

void Node::startSimulation() {
    running = true;
    simulationThread = std::thread(&Node::simulate, this);
}

void Node::stopSimulation() {
    running = false;
    cv.notify_all();
    simulationThread.join();
}

Node::~Node() {
    if (simulationThread.joinable()) {
        running = false;
        cv.notify_all();
        simulationThread.join();
    }
}


