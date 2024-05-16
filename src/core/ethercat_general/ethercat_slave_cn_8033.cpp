#include "ethercat_slave_cn_8033.h"

void EthercatSlave_CN_8033::CreatePDO()
{
    int val;
    //val = ecrt_slave_config_sdo8(this->slave_config, 0x1C12, 0x00, 0); /* set number of TxPDO */
    //val = ecrt_slave_config_sdo8(this->slave_config, 0x1C13, 0x00, 0); /* clear sm pdo 0x1c13 */
    //val = ecrt_slave_config_sdo16(this->slave_config, 0x1C13, 0x01, 0x1A00); /* upload pdo 1c13 index */
    //val = ecrt_slave_config_sdo8(this->slave_config, 0x1C13, 0x00, 1); /* set number of TxPDO */

    EthercatSlave::CreatePDO();
}