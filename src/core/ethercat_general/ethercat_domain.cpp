#include "ethercat_domain.h"
#include <iostream>

EthercatDomain::~EthercatDomain()
{
	delete[] regs;
	delete[] byte_position;
	delete[] bit_position;
}

void EthercatDomain::AddDefaultDomain(EthercatMaster* master, EthercatSlavesContainer* slaves)
{
	this->domain_request = ecrt_master_create_domain(master->GetRequest());
	if(!domain_request)
	{
		std::cout << ">>> Ethercat: failed to create domain.\n";
		return;
	}

	// Calculate quantity of PDOs
	uint32_t quantity_of_pdos = 0;
	auto slaves_map = slaves->GetMap();
	for(auto it_slave = slaves_map->begin(); it_slave != slaves_map->end(); ++it_slave)
	{
		auto rxpdo = it_slave->second->GetSync()->GetRxPDO();
		if(rxpdo)
		{
			quantity_of_pdos += rxpdo->GetSize();
		}

		auto txpdo = it_slave->second->GetSync()->GetTxPDO();
		if(txpdo)
		{
			quantity_of_pdos += txpdo->GetSize();
		}
	}

	this->regs = new ec_pdo_entry_reg_t[quantity_of_pdos + 1];
	this->byte_position = new uint32_t[quantity_of_pdos];
	this->bit_position = new uint32_t[quantity_of_pdos];

	uint32_t reg_index = 0;
	for(auto it_slave = slaves_map->begin(); it_slave != slaves_map->end(); ++it_slave)
	{
		auto slave = it_slave->second;

		auto rxpdo = slave->GetSync()->GetRxPDO();
		if(rxpdo)
		{
			for(auto it_pdo = rxpdo->GetMap()->begin(); it_pdo != rxpdo->GetMap()->end(); ++it_pdo)
			{
				regs[reg_index] = (const ec_pdo_entry_reg_t) {
				slave->GetAlias(),
				slave->GetPosition(),
				slave->GetVendorID(),
				slave->GetProductCode(),
				it_pdo->second->GetIndex(),
				it_pdo->second->GetSubindex(),
				byte_position + reg_index,
				bit_position + reg_index
			};
			reg_index++;
			}
		}

		auto txpdo = slave->GetSync()->GetTxPDO();
		if(txpdo)
		{
			for(auto it_pdo = txpdo->GetMap()->begin(); it_pdo != txpdo->GetMap()->end(); ++it_pdo)
			{
				regs[reg_index] = (const ec_pdo_entry_reg_t) {
				slave->GetAlias(),
				slave->GetPosition(),
				slave->GetVendorID(),
				slave->GetProductCode(),
				it_pdo->second->GetIndex(),
				it_pdo->second->GetSubindex(),
				byte_position + reg_index,
				bit_position + reg_index
			};
			reg_index++;
			}
		}

	}
	regs[reg_index] = {};

	if(ecrt_domain_reg_pdo_entry_list(this->domain_request, this->regs))
	{
		std::cerr << ">>> Ethercat: Domain PDO entry registration failed!\n";		
	}
}

void EthercatDomain::SetProcessData(EthercatSlavesContainer* slaves)
{
	this->domain_offset = ecrt_domain_data(this->domain_request);
	auto slaves_map = slaves->GetMap();
	uint32_t reg_index = 0;
	for(auto it_slave = slaves_map->begin(); it_slave != slaves_map->end(); ++it_slave)
	{
		auto slave = it_slave->second;
		auto rxpdo = slave->GetSync()->GetRxPDO();
		if(rxpdo)
		{
			for(auto it_pdo = rxpdo->GetMap()->begin(); it_pdo != rxpdo->GetMap()->end(); ++it_pdo)
			{
				it_pdo->second->RegisterDomainOffset(domain_offset);			
				it_pdo->second->RegisterBytePosition(byte_position[reg_index]);
				it_pdo->second->RegisterBitPosition(bit_position[reg_index]);
				reg_index++;
			}
		}

		auto txpdo = slave->GetSync()->GetTxPDO();
		if(txpdo)
		{
			for(auto it_pdo = txpdo->GetMap()->begin(); it_pdo != txpdo->GetMap()->end(); ++it_pdo)
			{
				it_pdo->second->RegisterDomainOffset(domain_offset);			
				it_pdo->second->RegisterBytePosition(byte_position[reg_index]);
				it_pdo->second->RegisterBitPosition(bit_position[reg_index]);
				reg_index++;
			}
		}
	}
}

ec_domain_t* EthercatDomain::GetRequest()
{
	return this->domain_request;
}

void EthercatDomain::Process()
{
	ecrt_domain_process(this->domain_request);
}
void EthercatDomain::Queue()
{
	ecrt_domain_queue(this->domain_request);
}