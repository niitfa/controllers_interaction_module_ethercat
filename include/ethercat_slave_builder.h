#ifndef ETHERCAT_SLAVE_BUILDER_H
#define ETHERCAT_SLAVE_BUILDER_H

#include "ethercat_slave.h"

class EthercatSlaveBuilder
{
    EthercatSlaveBuilder() = delete;
public:
    static EthercatSlave* BuildIOModule(uint16_t alias, uint16_t position);
    static EthercatSlave* BuildKVFilterDrive(uint16_t alias, uint16_t position);
    static EthercatSlave* BuildKVDetectorDrive(uint16_t alias, uint16_t position);
};

#endif