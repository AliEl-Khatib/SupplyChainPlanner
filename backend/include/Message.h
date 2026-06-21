#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>

struct Message {
    std::string from;
    std::string to;
    std::string product;
    int units;
    std::string type;  // "ORDER", "SHIPMENT", "PRODUCE"
};

#endif