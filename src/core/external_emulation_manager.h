#ifndef EXTERNAL_EMULATION_MANGAGER_H
#define EXTERNAL_EMULATION_MANGAGER_H

#include <map>
#include "mutual_access_synchronizer.h"
#include "emulated_event.h"

class ExternalEmulationManager
{
	std::map<EmulatedEvent*, void*> emulated_events;
	MutualAccessSynchronizer synchronizer;
public:
	void RunEvents();
	bool InsertEvent(EmulatedEvent*);
	bool RemoveEvent(EmulatedEvent*);
	bool RemoveEventUnsafe(EmulatedEvent*);
	void ClearEvents();
};

#endif

