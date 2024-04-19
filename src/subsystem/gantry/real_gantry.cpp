#include "real_gantry.h"
#include "ethercat_slave_names.h"
#include "coe_object_names.h"

using namespace ethercat_slave_names;
using namespace coe_object_names;

bool RealGantry::IsEmulated()
{
    return false;
}

void RealGantry::ModifyTelemetry()
{
	auto master_telemetry = context->GetTelemetryExchanger()->GetMasterTelemetry();
	auto gantry_drive = this->GetEthercatConfig()->GetSlaves()->GetSlave(kGantryDrive);

	master_telemetry->gantry_position_count 		= gantry_drive->GetRxPDOEntry(kActualPosition)->LoadValue();
	master_telemetry->gantry_velocity_count_per_sec = gantry_drive->GetTelemetrySDOEntry(kActualVelocity)->LoadValue();	
}
