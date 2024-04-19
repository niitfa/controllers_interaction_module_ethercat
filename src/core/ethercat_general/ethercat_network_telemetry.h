#ifndef ETHERCAT_NETWORK_TELEMETRY_H
#define ETHERCAT_NETWORK_TELEMETRY_H

#include <vector>
#include "ecrt.h"

/* See ec_*** structs definition in "ecrt.h" */	
struct EthercatNetworkTelemetry
{
	/* Master telemetry */
	ec_master_state_t master_state;
	/* Slaves telemetry */
	std::vector<ec_slave_info_t> slaves_info;
	/* Domain telemetry */
	ec_domain_state_t domain_state;	
};

#endif