#ifndef ECAT_SLAVE_BUILDER_H
#define ECAT_SLAVE_BUILDER_H

#include "ethercat_slave.h"

class EcatSlaveBuilder
{
public:
    virtual EthercatSlave* Build(uint16_t alias, uint16_t position) = 0;
};

#endif