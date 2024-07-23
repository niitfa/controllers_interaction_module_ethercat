#ifndef MAILBOX_STATE_H
#define MAILBOX_STATE_H

#include "mailbox_telemetry.h"
#include "sdo_list.h"
#include "state_content_creator.h"

class MailboxState : public StateContentCreator<class MailboxContext, class MailboxState, class MailboxManager, MaliboxTelemetry> 
{
protected:
	SDOList* sdos = nullptr;
	std::map<std::string, CoEServiceObject*>::iterator it;
public:
	~MailboxState();
	void SetSDOList(SDOList*);
};


#endif