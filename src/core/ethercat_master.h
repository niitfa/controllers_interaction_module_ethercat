#ifndef ETHERCATMASTER_H
#define ETHERCATMASTER_H

#include "ecrt.h"
#include "mailbox_manager.h"

class EthercatMaster
{
	ec_master_t* master_request = nullptr;
	int master_index;
public:
	EthercatMaster();
	~EthercatMaster();
	void SetMasterIndex(int);	
	void Request();
	ec_master_t* GetRequest();
	void Activate();
	void Release();
	void ReceiveProcessData();
	void SendProcessData();
private:
};

#endif