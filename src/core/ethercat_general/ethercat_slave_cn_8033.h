#ifndef ETHERCAT_SLAVE_CN_8033_H
#define ETHERCAT_SLAVE_CN_8033_H

#include "ethercat_slave.h"

class EthercatSlave_CN_8033 : public EthercatSlave
{
public:
    void CreatePDO() override;
};

#endif