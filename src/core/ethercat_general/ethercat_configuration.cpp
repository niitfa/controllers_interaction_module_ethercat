#include "ethercat_configuration.h"
#include "mailbox_reading_state.h"
#include "mailbox_writing_state.h"

EthercatConfiguration::EthercatConfiguration()
{
	domain = new EthercatDomain();
	telemetry_broker = new EthercatTelemetryBroker();
	mailbox = new MailboxManager();
}
EthercatConfiguration::~EthercatConfiguration()
{
	delete master;
	delete domain;
	delete timer;
	delete slaves;
	delete telemetry_broker;
	delete mailbox;
}

EthercatMaster* EthercatConfiguration::GetMaster()
{
	return this->master;
}

EthercatDomain* EthercatConfiguration::GetDomain() 
{
	return this->domain;
}

EthercatTimer* EthercatConfiguration::GetTimer()
{
	return this->timer;
}

EthercatSlavesContainer* EthercatConfiguration::GetSlaves() 
{
	return this->slaves;
}

EthercatSlave* EthercatConfiguration::GetSlave(std::string name)
{
	if(this->slaves)
	{
		return this->slaves->GetSlave(name);
	}
	return nullptr;
}

MailboxManager* EthercatConfiguration::GetMailbox()
{
	return this->mailbox;
}

void EthercatConfiguration::RegisterMaster(EthercatMaster* master)
{ 
	this->master = master;
}

void EthercatConfiguration::RegisterTimer(EthercatTimer* timer)
{
	this->timer = timer;
}

void EthercatConfiguration::RegisterSlavesContainer(EthercatSlavesContainer* slaves)
{ 
	this->slaves = slaves;
}

void EthercatConfiguration::Initialize()
{
	if (master && slaves && domain && timer)
	{
		master->Request();
		slaves->ConfigureAllSlaves(master);
		domain->AddDefaultDomain(master, slaves);
		timer->ConfigureClocks();	
		master->Activate();
		domain->SetProcessData(slaves);
		this->PrepareMailboxTasks();
	}
}

void EthercatConfiguration::Release()
{
	if (master && slaves && domain && timer)
	{
		master->Release();
	}
}

void EthercatConfiguration::PreProcessingAction()
{
	if (master && slaves && domain && timer)
	{
		master->ReceiveProcessData();

		ecrt_domain_state(domain->GetRequest(), &(GetMasterTelemetry()->domain_state));

		domain->Process();
		slaves->ReadProcessDataFromDomain();
		
		/* Optional */
		mailbox->Action();
		telemetry_broker->UpdateEthercatBufferTelemetry();
	}
}

void EthercatConfiguration::PostProcessingAction()
{
	if (master && slaves && domain && timer)
	{
		slaves->WriteProcessDataToDomain();
		domain->Queue();
		timer->SyncDistributedClocks(master);	
		master->SendProcessData();
		timer->UpdateMasterClock();
	}
}


void EthercatConfiguration::UpdateEthercatNetworkTelemetry()
{
	this->telemetry_broker->UpdateEthercatTelemetry();
}

void EthercatConfiguration::ModifyEthercatNetworkTelemetry()
{
	this->telemetry_broker->ModifyEthercatTelemetry(this);
}

const EthercatNetworkTelemetry* EthercatConfiguration::GetTelemetry()
{
	return telemetry_broker->GetClientEthercatTelemetry();
}

EthercatNetworkTelemetry* EthercatConfiguration::GetMasterTelemetry()
{
	return this->telemetry_broker->GetMasterEthercatTelemetry();
}

void EthercatConfiguration::PrepareMailboxTasks()
{
	SDOList* sdos_to_write = new SDOList();
	auto slaves_map = this->slaves->GetMap();
	for(auto it = slaves_map->begin(); it != slaves_map->end(); ++it)
	{
		if(it->second->GetParameterSDO())
		{
			sdos_to_write->MergeWith(it->second->GetParameterSDO());
		}
	}


	SDOList* sdos_to_read = new SDOList();
	for(auto it = slaves_map->begin(); it != slaves_map->end(); ++it)
	{
		if(it->second->GetTelemetrySDO())
		{
			sdos_to_read->MergeWith(it->second->GetTelemetrySDO());
		}
	}


	MailboxWritingState* write_mailbox_state = new MailboxWritingState();
	write_mailbox_state->SetSDOList(sdos_to_write);		
	MailboxReadingState* read_mailbox_state = new MailboxReadingState();
	read_mailbox_state->SetSDOList(sdos_to_read);

	MailboxState::StartQueueWith(write_mailbox_state)
		->WithNextTask(read_mailbox_state);

	mailbox->SetMailboxMode(write_mailbox_state);	
}
