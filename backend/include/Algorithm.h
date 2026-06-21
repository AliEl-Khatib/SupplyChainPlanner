#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "SupplyChainNetwork.h"
#include "json.hpp"

class Algorithm {
public:
    virtual void run(SupplyChainNetwork& network, std::string sourceId) = 0;
    virtual ~Algorithm();
    virtual nlohmann::json runAndReturn(SupplyChainNetwork& network, std::string sourceId) = 0;
};

#endif