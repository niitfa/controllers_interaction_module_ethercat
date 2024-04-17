#ifndef MAILBOX_READING_STATE_H
#define MAILBOX_READING_STATE_H

#include "mailbox_state.h"

class MailboxReadingState : public MailboxState
{
public:
	void StateRun() override;
};

#endif
