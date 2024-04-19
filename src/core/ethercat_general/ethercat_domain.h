#ifndef ETHERCAT_DOMAIN_H
#define ETHERCAT_DOMAIN_H

#include "ethercat_master.h"
#include "ethercat_slaves_container.h"
#include "ecrt.h"

class EthercatDomain
{
	ec_domain_t* domain_request = nullptr;
	ec_pdo_entry_reg_t* regs = nullptr;
	uint32_t* byte_position = nullptr;
	uint8_t* domain_offset = nullptr;
	uint32_t* bit_position = nullptr;
public:
	EthercatDomain() = default;
	~EthercatDomain();
	void AddDefaultDomain(EthercatMaster*, EthercatSlavesContainer*);
	void SetProcessData(EthercatSlavesContainer*);
	ec_domain_t* GetRequest();
	void Process();
	void Queue();
};

#endif