#ifndef MAILBOX_MANAGER_H
#define MAILBOX_MANAGER_H

#include "mailbox_telemetry.h"
#include "mailbox_state.h"
#include "mailbox_context.h"

class MailboxManager
{
	MailboxContext* context = new MailboxContext();
public:
	MailboxManager();
	~MailboxManager();
	void SetMailboxMode(MailboxState*);
	void Action();
};

#endif