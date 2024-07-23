#ifndef IO_MODULE_MKLKT_BUILDER_H
#define IO_MODULE_MKLKT_BUILDER_H

#include "ecat_slave_builder.h"

class IOModuleMKLKTBuilder : public EcatSlaveBuilder
{
public:
    EthercatSlave* Build(uint16_t alias, uint16_t position) override;
};

#endif