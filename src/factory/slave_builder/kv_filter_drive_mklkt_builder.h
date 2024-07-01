#ifndef KV_FILTER_DRIVE_MKLKT_BUILDER_H
#define KV_FILTER_DRIVE_MKLKT_BUILDER_H

#include "ecat_slave_builder.h"

class KVFilterDriveMKLKTBuilder : public EcatSlaveBuilder
{
public:
    EthercatSlave* Build(uint16_t alias, uint16_t position) override;
};

#endif