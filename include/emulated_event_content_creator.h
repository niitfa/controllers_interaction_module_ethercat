#ifndef EMULATED_EVENT_CONTENT_CREATOR_H
#define EMULATED_EVENT_CONTENT_CREATOR_H

#include "emulated_event.h"
#include "external_emulation_manager.h"

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