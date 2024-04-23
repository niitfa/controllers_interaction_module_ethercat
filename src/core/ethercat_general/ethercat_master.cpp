#include "ethercat_master.h"
#include <iostream>

EthercatMaster::EthercatMaster()
{
}

EthercatMaster::~EthercatMaster()
{
}

void EthercatMaster::Request()
{
	this->master_request = ecrt_request_master(master_index);
	if(!master_request)
	{
		std::cerr << ">>> Ethercat: failed to request master " << master_index << "\n";
		return;
	}
	std::cerr << ">>> Ethercat: master " << master_index << " is requested successfully.\n";
}

ec_master_t* EthercatMaster::GetRequest()
{
	return this->master_request;
}

void EthercatMaster::SetMasterIndex(int master_ind)
{
	this->master_index = master_ind;
}

void EthercatMaster::Activate()
{
	if (ecrt_master_activate(this->master_request)) {
		std::cerr << ">>> Ethercat: failed to activate master " << master_index << ".\n";
    	return;
	}
	std::cerr << ">>> Ethercat: activating master " << master_index << ".\n";
}

void EthercatMaster::Release()
{
	ecrt_release_master(this->master_request);
}
void EthercatMaster::ReceiveProcessData()
{
	ecrt_master_receive(this->master_request);
}
void EthercatMaster::SendProcessData()
{
	ecrt_master_send(this->master_request);	
}