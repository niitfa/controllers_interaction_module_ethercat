#include "mailbox_reading_state.h"
#include "mailbox_context.h"

void MailboxReadingState::StateRun()
{
    if (this->sdos)
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
    else
    {
        MailboxState::GetContext()->TransitToNext();	
    }
}