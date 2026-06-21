#ifndef NODE_H
#define NODE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <string>
#include "Message.h"
#include <unordered_map>

class Node {
private:
    std::string id;
    std::string name;
    std::string location;
    bool running = false;
    std::queue<Message> inbox;
    std::mutex mtx;
    std::condition_variable cv;
    std::thread simulationThread;
    std::vector<Node*> neighbors;
    std::unordered_map<std::string, int> inventory;

public:
    // constructor
    Node(std::string id, std::string name, std::string location);

    // getters
    std::string getId() const;
    std::string getName() const;
    std::string getLocation() const;
    std::vector<Node*> getNeighbors() const;
    std::unordered_map<std::string, int> getInventory() const;
    void addToInventory(std::string product, int units);
    void takeFromInventory(std::string product, int units);

    bool getRunning() const;

    void sendMessage(Message msg);
    Message receiveMessage();
    virtual void simulate() = 0;
    void startSimulation();
    void stopSimulation();
    void addNeighbor(Node* neighbor);

    // display info
    virtual void display() const;

    // virtual destructor
    virtual ~Node();
};

#endif
