#ifndef SUBSYSTEM_CONTENT_CREATOR_H
#define SUBSYSTEM_CONTENT_CREATOR_H

#include "external_emulation_manager.h"
#include "subsystem.h"

template<class TContext, class TState, class TSubsystem, class TTelemetry>
class SubsystemContentCreator : public Subsystem
{
protected:
	TContext* context = new TContext();
	ExternalEmulationManager* external_emulation_impacts = new ExternalEmulationManager();
public:
	SubsystemContentCreator();
	~SubsystemContentCreator();
	
	void Action() override;
	void UpdateSubsystemTelemetry() override;
	void SetTask(TState*);
	const TTelemetry* GetTelemetry();
	virtual bool IsEmulated() = 0;

	void InsertEmulationEvent(EmulatedEventContentCleator<TContext>*);
	void RemoveEmulationEvent(EmulatedEventContentCleator<TContext>*);
	void RemoveEmulationEventUnsafe(EmulatedEventContentCleator<TContext>*);
	void ClearAllEmulationEvents();
};


template<class TContext, class TState, class TSubsystem, class TTelemetry>
SubsystemContentCreator<TContext, TState, TSubsystem, TTelemetry>::SubsystemContentCreator()
{
	this->context->PassSubsystem((TSubsystem*)this);
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
SubsystemContentCreator<TContext, TState, TSubsystem, TTelemetry>::~SubsystemContentCreator()
{
	delete context;
	delete external_emulation_impacts;
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
void SubsystemContentCreator<TContext, TState, TSubsystem, TTelemetry>::Action()
{
	this->context->SyncContextRun();
	if(this->IsEmulated())
	{
		this->external_emulation_impacts->RunEvents();
	}
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
void SubsystemContentCreator<TContext, TState, TSubsystem, TTelemetry>::UpdateSubsystemTelemetry()
{
	this->context->GetTelemetryExchanger()->UpdateClientTelemetry();
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
void SubsystemContentCreator<TContext, TState, TSubsystem, TTelemetry>::SetTask(TState* task)
{
	this->context->SyncTransit(task);
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
const TTelemetry* SubsystemContentCreator<TContext, TState, TSubsystem, TTelemetry>::GetTelemetry()
{
	return this->context->GetTelemetryExchanger()->GetClientTelemetry();
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
void SubsystemContentCreator<TContext, TState, TSubsystem, TTelemetry>::InsertEmulationEvent(EmulatedEventContentCleator<TContext>* event)
{
	if(event && this->IsEmulated())
	{
		event->StoreContext((TContext*)this->context);
		this->external_emulation_impacts->InsertEvent(event);
	}
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
void SubsystemContentCreator<TContext, TState, TSubsystem, TTelemetry>::RemoveEmulationEvent(EmulatedEventContentCleator<TContext>* event)
{
	if(event && this->IsEmulated())
	{
		this->external_emulation_impacts->RemoveEvent(event);
	}
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
void SubsystemContentCreator<TContext, TState, TSubsystem, TTelemetry>::RemoveEmulationEventUnsafe(EmulatedEventContentCleator<TContext>* event)
{
	if(event && this->IsEmulated())
	{
		this->external_emulation_impacts->RemoveEventUnsafe(event);
	}
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
void SubsystemContentCreator<TContext, TState, TSubsystem, TTelemetry>::ClearAllEmulationEvents()
{
	if(this->IsEmulated())
	{
		this->external_emulation_impacts->ClearEvents();
	}
}

#endif