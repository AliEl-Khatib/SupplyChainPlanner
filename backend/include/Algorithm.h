#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "SupplyChainNetwork.h"

class Algorithm {
public:
    virtual void run(SupplyChainNetwork& network, std::string sourceId) = 0;
    virtual ~Algorithm();
};

#endif