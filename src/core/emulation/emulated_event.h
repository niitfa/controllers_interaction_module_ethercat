#ifndef EMULATED_EVENT_H
#define EMULATED_EVENT_H

#include <atomic>

class EmulatedEvent
{
	std::atomic<bool> is_event_completed;		
public:
	EmulatedEvent();
	virtual ~EmulatedEvent() = default;
	virtual void RunEvent() = 0;
	bool IsCompleted();
protected:
	void EndThisEvent();	
};

#endif