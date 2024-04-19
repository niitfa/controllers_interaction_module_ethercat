#ifndef CONTEXT_H
#define CONTEXT_H

#include "mutual_access_synchronizer.h"
#include "telemetry_exchanger.h"

template<class TContext, class TState, class TSubsystem, class TTelemetry>
class ContextContentCreator
{
	TState* state = nullptr;
	TSubsystem* subsystem = nullptr;
	MutualAccessSynchronizer synchronizer;
	TelemetryExchanger<TTelemetry> telemetry_exchanger;
protected:
	class EmptyState : public TState
	{
	public:
		void StateRun() override {}
	};
public:
	ContextContentCreator();
	void Transit(TState*);
	void TransitToNext();
	void SyncTransit(TState*);
	void ContextRun();
	void SyncContextRun();
	TSubsystem* GetSubsystem();
	void PassSubsystem(TSubsystem* subsystem);
	MutualAccessSynchronizer* GetSynchronizer();
	TelemetryExchanger<TTelemetry>* GetTelemetryExchanger();
};

template<class TContext, class TState, class TSubsystem, class TTelemetry>
ContextContentCreator<TContext, TState, TSubsystem, TTelemetry>::ContextContentCreator()
{
	this->Transit(new EmptyState());
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
void ContextContentCreator<TContext, TState, TSubsystem, TTelemetry>::Transit(TState* target_state)
{
	if (this->state) delete this->state;
	this->state = target_state;
	this->state->SetContext((TContext*)this);	
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
void ContextContentCreator<TContext, TState, TSubsystem, TTelemetry>::TransitToNext()
{
	if(this->state->GetNextTask())
	{
		this->Transit(this->state->GetNextTask());
	}
	else
	{
		this->Transit(new EmptyState());
	}
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
void ContextContentCreator<TContext, TState, TSubsystem, TTelemetry>::SyncTransit(TState* target_state)
{
	this->GetSynchronizer()->Lock();
	if (target_state)
	{
		this->Transit(target_state);
	}
	this->GetSynchronizer()->Unlock();
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
void ContextContentCreator<TContext, TState, TSubsystem, TTelemetry>::ContextRun()
{
	if(this->state)
	{
		this->state->StateRun();
	}
	this->GetTelemetryExchanger()->UpdateBufferTelemetry();
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
void ContextContentCreator<TContext, TState, TSubsystem, TTelemetry>::SyncContextRun()
{
	if (GetSynchronizer()->Trylock())
	{
		ContextRun();
		GetSynchronizer()->Unlock();
	}
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
TSubsystem* ContextContentCreator<TContext, TState, TSubsystem, TTelemetry>::GetSubsystem()
{
	return this->subsystem;
}


template<class TContext, class TState, class TSubsystem, class TTelemetry>
void ContextContentCreator<TContext, TState, TSubsystem, TTelemetry>::PassSubsystem(TSubsystem* subsystem)
{
	this->subsystem = subsystem;
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
MutualAccessSynchronizer* ContextContentCreator<TContext, TState, TSubsystem, TTelemetry>::GetSynchronizer()
{
	return &this->synchronizer;
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
TelemetryExchanger<TTelemetry>* ContextContentCreator<TContext, TState, TSubsystem, TTelemetry>::GetTelemetryExchanger()
{
	return &this->telemetry_exchanger;
}

#endif