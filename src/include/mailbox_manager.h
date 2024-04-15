#ifndef MAILBOXMANAGER_H
#define MAILBOXMANAGER_H

#include "sdo_list.h"
#include "state_content_creator.h"
#include "context_content_creator.h"

struct MaliboxTelemetry
{
	/* заглушка */
};

class MailboxContext;
class MailboxState;
class MailboxManager;

class MailboxState : public StateContentCreator<MailboxContext, MailboxState, MailboxManager, MaliboxTelemetry> 
{
protected:
	SDOList* sdos = nullptr;
	std::map<std::string, CoEServiceObject*>::iterator it;
public:
	~MailboxState();
	void SetSDOList(SDOList*);
};

class MailboxContext : public ContextContentCreator<MailboxContext, MailboxState, MailboxManager, MaliboxTelemetry>
{};

class MailboxManager
{
	MailboxContext* context = new MailboxContext();
public:
	MailboxManager();
	~MailboxManager();
	void SetMailboxMode(MailboxState*);
	void Action();
};

class MailboxWritingState : public MailboxState
{
public:
	void StateRun() override;
};

class MailboxReadingState : public MailboxState
{
public:
	void StateRun() override;
};

#endif