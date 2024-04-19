#ifndef STATE_CONTENT_CREATOR_H
#define STATE_CONTENT_CREATOR_H

#include "mutual_access_synchronizer.h"
#include "telemetry_exchanger.h"

template<class TContext, class TState, class TSubsystem, class TTelemetry>
class StateContentCreator
{
	TContext* context = nullptr;
	TState* next_state = nullptr;
	MutualAccessSynchronizer synchronizer;
public:
	StateContentCreator();
	virtual ~StateContentCreator() = default;
	void SetContext(TContext*);
	TContext* GetContext();
	static TState* StartQueueWith(TState*);
	TState* WithNextTask(TState*);
	TState* GetNextTask();
	TTelemetry* GetMasterTelemetry();
	virtual void StateRun() = 0;
};

/* STATE DEFINITIONS */
template<class TContext, class TState, class TSubsystem, class TTelemetry>
StateContentCreator<TContext, TState, TSubsystem, TTelemetry>::StateContentCreator()
{}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
void StateContentCreator<TContext, TState, TSubsystem, TTelemetry>::SetContext(TContext* context)
{
	this->context = context;
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
TContext* StateContentCreator<TContext, TState, TSubsystem, TTelemetry>::GetContext()
{
	return this->context;
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
TState* StateContentCreator<TContext, TState, TSubsystem, TTelemetry>::StartQueueWith(TState* root_state)
{
	return root_state;
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
TState* StateContentCreator<TContext, TState, TSubsystem, TTelemetry>::WithNextTask(TState* next_state)
{
	return this->next_state = next_state;
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
TState* StateContentCreator<TContext, TState, TSubsystem, TTelemetry>::GetNextTask()
{
	return this->next_state;
}

template<class TContext, class TState, class TSubsystem, class TTelemetry>
TTelemetry* StateContentCreator<TContext, TState, TSubsystem, TTelemetry>::GetMasterTelemetry()
{
	return this->GetContext()->GetTelemetryExchanger()->GetMasterTelemetry();
}

#endif