#ifndef KV_DETECTOR_DRIVE_MKLKT_BUILDER_H
#define KV_DETECTOR_DRIVE_MKLKT_BUILDER_H

#include "ecat_slave_builder.h"

class KVDetectorDriveMKLKTBuilder : public EcatSlaveBuilder
{
public:
    EthercatSlave* Build(uint16_t alias, uint16_t position) override;
};

#endif