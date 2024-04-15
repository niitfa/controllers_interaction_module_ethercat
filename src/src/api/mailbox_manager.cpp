#include "mailbox_manager.h"
#include <bitset>

// MailboxState

MailboxState::~MailboxState()
{}

void MailboxState::SetSDOList(SDOList* sdo_list)
{
	this->sdos = sdo_list;
	this->it = sdos->GetMap()->begin();
}

// MailboxManager
MailboxManager::MailboxManager()
{}

MailboxManager::~MailboxManager()
{
	delete context;
}

void MailboxManager::SetMailboxMode(MailboxState* target_state)
{
	if (this->context && target_state)
	{
		this->context->Transit(target_state);
	}
}

void MailboxManager::Action()
{
	if (this->context)
	{
		this->context->ContextRun();
	}
}

// MailboxReadingState
void MailboxReadingState::StateRun()
{
	if(sdos->GetMap()->empty())
	{
		MailboxState::GetContext()->TransitToNext();
		return;
	}	

	if(it->second->ReadTypeRequest())
	{
		++it;
	}

	if(it == this->sdos->GetMap()->end())
	{
		it = this->sdos->GetMap()->begin();
	}
}

//MailboxWritingState
void MailboxWritingState::StateRun()
{
	if(it != this->sdos->GetMap()->end())
	{
		if(it->second->WriteTypeRequest())
		{
			++it;
		}
		return;
	}
	MailboxState::GetContext()->TransitToNext();	
}



