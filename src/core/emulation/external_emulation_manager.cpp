#include "external_emulation_manager.h"

void ExternalEmulationManager::RunEvents()
{

	if(this->synchronizer.Trylock())
	{
		/* Run */
		for (auto it = emulated_events.begin(); it != emulated_events.end(); ++it)
		{
			std::cout << emulated_events.size() << std::endl;;
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
	bool inserted;	

	this->synchronizer.Lock();
	auto event_it = emulated_events.find(event);
	if(event_it == emulated_events.end() && event)
	{
		emulated_events.emplace(event, nullptr);
		inserted = true;
	}
	else
	{
		inserted = false;
	}
	this->synchronizer.Unlock();

	return inserted;
}

bool ExternalEmulationManager::RemoveEvent(EmulatedEvent* event)
{	
	this->synchronizer.Lock();
	bool removed = this->RemoveEventUnsafe(event);
	this->synchronizer.Unlock();

	return removed;
}

bool ExternalEmulationManager::RemoveEventUnsafe(EmulatedEvent* event)
{
	bool removed;

	auto event_it = emulated_events.find(event);
	if(event_it != emulated_events.end())
	{
		emulated_events.erase(event_it);
		delete event_it->first;
		removed = true;
	}
	else
	{
		removed = false;
	}

	return removed;
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

