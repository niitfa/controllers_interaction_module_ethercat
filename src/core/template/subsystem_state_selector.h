#ifndef SUBSYSTEM_STATE_SELECTOR_H
#define SUBSYSTEM_STATE_SELECTOR_H

template<class TSubsystem, class TBasicState, class TRealState, class TEmulatedState>
class SubsystemStateSelector
{
public:
	static TBasicState* CreateTaskFor(TSubsystem*);
};

template<class TSubsystem, class TBasicState, class TRealState, class TEmulatedState>
TBasicState* SubsystemStateSelector<TSubsystem, TBasicState, TRealState, TEmulatedState>::CreateTaskFor(TSubsystem* subsystem)
{
	if(subsystem)
	{
		if(subsystem->IsEmulated())
		{
			return new TEmulatedState;
		}
		return new TRealState;
	}
	return nullptr;
}

#endif