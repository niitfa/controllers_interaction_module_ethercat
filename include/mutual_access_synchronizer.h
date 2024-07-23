#ifndef MUTUAL_ACCESS_SYNCHRONIZER_H
#define MUTUAL_ACCESS_SYNCHRONIZER_H

#include <iostream>
#include <mutex>

class MutualAccessSynchronizer
{
	std::mutex mtx;
public:
	void Lock()
	{
		mtx.lock();
	}
	void Unlock()
	{
		mtx.unlock();
	}
	bool Trylock()
	{
		return mtx.try_lock();
	}
};

#endif
