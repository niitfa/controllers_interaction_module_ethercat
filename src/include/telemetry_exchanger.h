#ifndef TELEMETRYEXCHANGER_H
#define TELEMETRYEXCHANGER_H

#include "mutual_access_synchronizer.h"

template<class TTelemetryData> /* TTelemetry is a struct with telemetry fields for concrete subsystem */
class TelemetryExchanger
{
	TTelemetryData* client_telemetry = new TTelemetryData; 
	TTelemetryData* buffer_telemetry = new TTelemetryData;
	TTelemetryData* master_telemetry = new TTelemetryData;
	MutualAccessSynchronizer synchronizer;
public:
	~TelemetryExchanger();
	bool UpdateClientTelemetry(); /* buffer -> client */
	bool UpdateBufferTelemetry(); /* master -> buffer */
	const TTelemetryData* GetClientTelemetry();
	TTelemetryData* GetMasterTelemetry();
};

template<class TTelemetryData>
TelemetryExchanger<TTelemetryData>::~TelemetryExchanger()
{
	delete client_telemetry;
	delete buffer_telemetry;
	delete master_telemetry;
}

template<class TTelemetryData>
bool TelemetryExchanger<TTelemetryData>::UpdateClientTelemetry() /* called from CLIENT thread */
{
	synchronizer.Lock();
	*client_telemetry = *buffer_telemetry;
	synchronizer.Unlock();
	return true;
}

template<class TTelemetryData>
bool TelemetryExchanger<TTelemetryData>::UpdateBufferTelemetry() /* called from ETHERCAT thread */
{
	if(synchronizer.Trylock())
	{
		*buffer_telemetry = *master_telemetry;
		synchronizer.Unlock();
		return true;
	}
	return false;
}

template<class TTelemetryData>
const TTelemetryData* TelemetryExchanger<TTelemetryData>::GetClientTelemetry() /* called from CLIENT thread */
{
	return client_telemetry;
}

template<class TTelemetryData>
TTelemetryData* TelemetryExchanger<TTelemetryData>::GetMasterTelemetry() /* called from ETHERCAT thread */
{
	return master_telemetry;
}

#endif