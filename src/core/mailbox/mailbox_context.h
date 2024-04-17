#ifndef MAILBOX_CONTEXT_H
#define MAILBOX_CONTEXT_H

#include "context_content_creator.h"
#include "mailbox_telemetry.h"

class MailboxContext : public ContextContentCreator<class MailboxContext, class MailboxState, class MailboxManager, MaliboxTelemetry>
{
};

#endif