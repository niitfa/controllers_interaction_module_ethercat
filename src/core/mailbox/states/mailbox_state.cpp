#include "mailbox_state.h"

MailboxState::~MailboxState() = default;

void MailboxState::SetSDOList(SDOList* sdo_list)
{
	this->sdos = sdo_list;
	this->it = sdos->GetMap()->begin();
}
