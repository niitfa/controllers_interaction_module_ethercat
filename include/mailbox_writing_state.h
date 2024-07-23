#ifndef MAILBOX_WRITING_STATE_H
#define MAILBOX_WRITING_STATE_H

#include "mailbox_state.h"

class MailboxWritingState : public MailboxState
{
public:
	void StateRun() override;
};

#endif