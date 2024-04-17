#include "external_emulation_manager.h"

bool EmulatedEvent::IsCompleted()
{
	return this->is_event_completed.load();
}

void EmulatedEvent::EndThisEvent()
{
	this->is_event_completed.store(true);
}

void ExternalEmulationManager::RunEvents()
{
	if(this->synchronizer.Trylock())
	{
		/* Run */
		for (auto it = emulated_events.begin(); it != emulated_events.end(); ++it)
		{
			it->first->RunEvent();
		}

		/* Clear if completed */
		for (auto it = emulated_events.begin(); it != emulated_events.end();)
		{
			if(it->first->IsCompleted())
			{
				this->RemoveEventUnsafe(it->first);
				it = emulated_events.begin();
			}
			else
			{
				++it;
			}
		}
		this->synchronizer.Unlock();
	}
}
	
bool ExternalEmulationManager::InsertEvent(EmulatedEvent* event)
{
	bool res;	

	this->synchronizer.Lock();
	auto event_it = emulated_events.find(event);
	if(event_it == emulated_events.end() && event)
	{
		emulated_events.emplace(event, nullptr);
		res = true;
	}
	else
	{
		res = false;
	}
	this->synchronizer.Unlock();

	return res;
}

bool ExternalEmulationManager::RemoveEvent(EmulatedEvent* event)
{	
	this->synchronizer.Lock();
	bool res = this->RemoveEventUnsafe(event);
	this->synchronizer.Unlock();

	return res;
}

bool ExternalEmulationManager::RemoveEventUnsafe(EmulatedEvent* event)
{
	bool res;

	auto event_it = emulated_events.find(event);
	if(event_it != emulated_events.end())
	{
		emulated_events.erase(event_it);
		delete event_it->first;
		res = true;
	}
	else
	{
		res = false;
	}

	return res;
}

void ExternalEmulationManager::ClearEvents()
{
	this->synchronizer.Lock();
	for (auto it = emulated_events.begin(); it != emulated_events.end(); ++it)
	{
		delete it->first;
	}
	emulated_events.clear();
	this->synchronizer.Unlock();
} 

