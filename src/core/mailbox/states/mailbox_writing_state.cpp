#include "mailbox_writing_state.h"
#include "mailbox_context.h"

void MailboxWritingState::StateRun()
{
    if(this->sdos)
    {
        if(it != this->sdos->GetMap()->end())
        {
            if(it->second->WriteTypeRequest())
            {
                ++it;
            }
            return;
        }
    }
	MailboxState::GetContext()->TransitToNext();	
}
