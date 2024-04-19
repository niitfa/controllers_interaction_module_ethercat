#include "emulated_event.h"

EmulatedEvent::EmulatedEvent()
{
    is_event_completed.store(false);
}

bool EmulatedEvent::IsCompleted()
{
	return this->is_event_completed.load();
}

void EmulatedEvent::EndThisEvent()
{
	this->is_event_completed.store(true);
}
