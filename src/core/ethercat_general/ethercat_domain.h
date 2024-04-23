/**
 * @brief Contains ethercat domain properties and methods.
 * Member of EthecatConfiguration.
 * @warning Must NOT be created by user!
 * @see EthercatConfiguration.
*/

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
	/**
	 * @brief Creates domain from ethercat slaves PDOs.
	 * @param[in] EthercatMaster* pointer to configured EthercatMaster instance
	 * (as member of EthercatConfiguration).
	 * @param[in] EthercatSlavesContainer* pointer to configured EthercatSlavesContainer instance
	 * (as member of EthercatConfiguration)
	*/
	void AddDefaultDomain(EthercatMaster*, EthercatSlavesContainer*);
	/**
	 * @brief Defines memory adress (offset) for each domain object.
	 * @param[in] EthercatSlavesContainer* pointer to configured EthercatSlavesContainer instance
	 * (as member of EthercatConfiguration)
	*/
	void SetProcessData(EthercatSlavesContainer*);
	/**
	 * @brief Gets domain request.
	*/
	ec_domain_t* GetRequest();
	/**
	 * @brief Wrapper of IgH function void ecrt_domain_process(ec_domain_t*)
	*/
	void Process();
	/**
	 * @brief Wrapper of IgH function void ecrt_domain_queue(ec_domain_t*)
	*/
	void Queue();
};

#endif