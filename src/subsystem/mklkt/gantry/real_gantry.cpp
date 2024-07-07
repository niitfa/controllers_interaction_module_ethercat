#include "real_gantry.h"
#include "ethercat_slave_names.h"
#include "coe_object_names.h"

using namespace ethercat_slave_names;
using namespace coe_object_names;

RealGantry::RealGantry(uint32_t microstep_resolution, float gear_ratio) : Gantry(microstep_resolution, gear_ratio)
{}

bool RealGantry::IsEmulated()
{
    return false;
}

void RealGantry::ModifyTelemetry()
{
	auto master_telemetry = context->GetTelemetryExchanger()->GetMasterTelemetry();
	
	master_telemetry->gantry_position_count 		= this->drive->GetTxPDOEntry(kActualPosition)->LoadValue();
}
