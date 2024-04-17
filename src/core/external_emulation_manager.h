#ifndef EMULATEDEVENT_H
#define EMULATEDEVENT_H

#include <vector>
#include <map>
#include <iostream>
#include <atomic>
#include "mutual_access_synchronizer.h"

class ExternalEmulationManager;

class EmulatedEvent
{
	std::atomic<bool> is_event_completed;		
public:
	EmulatedEvent() { is_event_completed.store(false); }
	virtual ~EmulatedEvent() = default;
	virtual void RunEvent() = 0;
	bool IsCompleted();
protected:
	void EndThisEvent();	
};

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

template<class TContext>
class EmulatedEventContentCleator : public EmulatedEvent
{
protected:
	ExternalEmulationManager* emulaton_manager = nullptr;
	TContext* context = nullptr;
public:
	void StoreContext(TContext*);
};

template<class TContext>
void EmulatedEventContentCleator<TContext>::StoreContext(TContext* context)
{
	this->context = context;
} 

#endif

