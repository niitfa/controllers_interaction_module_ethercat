/**
 * @brief Operates with all ethercat slaves in network.
 * Member of EthercatConfiguration.
 * @details Configuration example:
 * @code
 * #include "ethercat_slaves_container.h"
 * #include "ethercat_slave.h"
 * 
 * void ConfigureEthercatSlavesContainer()
 * {
 * 		EthercatSlave *slave_1, *slave_2, *slave_3;
 * 
 * 		// let's say slave_1, slave_2, slave_3 were previously
 * 		// configured (see EthercatSlave example in class description)
 * 
 * 		EthercatSlavesContainer* slaves = new EthercatSlavesContainer();
 * 		slaves->RegisterSlave(slave_1);
 * 		slaves->RegisterSlave(slave_2);
 * 		slaves->RegisterSlave(slave_3);	
 * }
 * @endcode
 * @see EthercatSlave, EthercatConfiguration
*/

#ifndef ETHERCAT_SLAVES_CONTAINER_H
#define ETHERCAT_SLAVES_CONTAINER_H

#include "ethercat_slave.h"
#include "ethercat_master.h"
#include <map>
#include <string>

class EthercatSlavesContainer
{
	std::map<std::string, EthercatSlave*> slaves;
public:
	~EthercatSlavesContainer();
	/**
	 * @brief Adds slave to container.
	 * @param[in] slave Slave for adding. 
	*/
	void RegisterSlave(EthercatSlave* slave);
	/**
	 * @brief Configures slaves
	 * @param[in] master Ethercat master which slaves must be configured for.
	 * @warning Must NOT be used by user!
	*/
	void ConfigureAllSlaves(EthercatMaster* master);
	/**
	 * @brief Finds ethercat slave in container by name and returns it's pointer.
	 * @param[in] name Name of the ethercat slave.
	 * @returns Pointer to ethercat slave with given name if it exists
	 * in container, otherwise returns nullptr.
	 * @warning Must NOT be called by user!
	*/
	EthercatSlave* GetSlave(std::string name);
	/**
	 * @brief Gets number of slaves in container.
	 * @returns Number of registered slaves.
	 * @warning Must NOT be called by user!
	*/
	uint16_t GetSize();
	/**
	 * @brief Provides direct access to slaves' map.
	 * @returns Pointer to slaves' map.
	 * @warning Must NOT be called by user!
	*/
	std::map<std::string, EthercatSlave*>* GetMap();
	/**
	 * @brief Saves values in domain to local CoE objects.
	 * @warning Must NOT be called by user!
	*/
	void ReadProcessDataFromDomain();
	/**
	 * @brief Loads values from local CoE objects to domain.
	 * @warning Must NOT be called by user!
	*/	
	void WriteProcessDataToDomain();
};


#endif