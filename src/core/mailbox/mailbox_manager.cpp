#include "mailbox_manager.h"
#include <bitset>

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

