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
                //std::cout << "MailboxWritingState::StateRun(): " << it->second->GetName() << " written value " << it->second->LoadValue() << std::endl;
                ++it;
            }
            return;
        }
    }
	MailboxState::GetContext()->TransitToNext();	
}
