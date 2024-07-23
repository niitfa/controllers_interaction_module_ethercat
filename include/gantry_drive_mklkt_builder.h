#ifndef GANTRY_DRIVE_MKLKT_H
#define GANTRY_DRIVE_MKLKT_H

#include "ecat_slave_builder.h"

class GantryDriveMKLKTBuilder : public EcatSlaveBuilder
{
public:
    EthercatSlave* Build(uint16_t alias, uint16_t postion) override;
};

#endif