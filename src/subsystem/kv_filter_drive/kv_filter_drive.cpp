#include "kv_filter_drive.h"
#include "debug_logger.h"
#include "coe_object_names.h"
#include "ethercat_slave_names.h"

KVFilterDrive::~KVFilterDrive()
{
    delete wire_sensor;
}

KVFilterDrive::KVFilterDrive(uint32_t microstep_resolution, float thread_pitch)
{
    this->props.microstep_resolution = microstep_resolution;
    this->props.thread_pitch = thread_pitch;

    //logger.CreateStorage(4, 25 * 1000, "kv_drive.txt");
}

void KVFilterDrive::Action()
{
    auto telemetry = this->context->GetTelemetryExchanger()->GetMasterTelemetry();
    /*logger.PlaceData(
        {
            telemetry->drive_position_mm,
            telemetry->drive_velocity_mm_per_sec,
            telemetry->wire_sensor_position_mm,
            telemetry->wire_sensor_velocity_mm_per_sec
        }
    ); */

    /*
    sdo_telemetry->AddObject("Synchronization type 0", 	0x1c32, 0x01, 16);
	sdo_telemetry->AddObject("Output shift time 0", 	0x1c32, 0x03, 32);
	sdo_telemetry->AddObject("Calc and copy time 0", 	0x1c32, 0x06, 32);
	sdo_telemetry->AddObject("Delay time 0", 			0x1c32, 0x09, 32);

	sdo_telemetry->AddObject("Synchronization type 1", 	0x1c33, 0x01, 16);
	sdo_telemetry->AddObject("Input shift time 1", 		0x1c33, 0x03, 32);
	sdo_telemetry->AddObject("Calc and copy time 1", 	0x1c33, 0x06, 32);
	sdo_telemetry->AddObject("Delay time 1", 			0x1c33, 0x09, 32);*/

    std::string slave_name = ethercat_slave_names::kKVFilterDriveName;

    std::cout << "KVFilterDrive::Action(): " 
        << "0x1c32:01 = "<< this->GetEthercatConfig()->GetSlave(slave_name)->GetTelemetrySDOEntry("Synchronization type 0")->LoadValue() + 0<< "\t"
        << "0x1c32:02 = "<< this->GetEthercatConfig()->GetSlave(slave_name)->GetTelemetrySDOEntry("Cycle time 0")->LoadValue() + 0<< "\t"
        << "0x1c32:03 = "<< this->GetEthercatConfig()->GetSlave(slave_name)->GetTelemetrySDOEntry("Output shift time 0")->LoadValue() + 0<< "\t"
        << "0x1c32:06 = "<< this->GetEthercatConfig()->GetSlave(slave_name)->GetTelemetrySDOEntry("Calc and copy time 0")->LoadValue() + 0<< "\t"
        << "0x1c32:09 = "<< this->GetEthercatConfig()->GetSlave(slave_name)->GetTelemetrySDOEntry("Delay time 0")->LoadValue() + 0<< "\t"
        << "0x1c33:01 = "<< this->GetEthercatConfig()->GetSlave(slave_name)->GetTelemetrySDOEntry("Synchronization type 1")->LoadValue() + 0<< "\t"
        << "0x1c33:02 = "<< this->GetEthercatConfig()->GetSlave(slave_name)->GetTelemetrySDOEntry("Cycle time 1")->LoadValue() + 0<< "\t"
        << "0x1c33:03 = "<< this->GetEthercatConfig()->GetSlave(slave_name)->GetTelemetrySDOEntry("Input shift time 1")->LoadValue() + 0<< "\t"
        << "0x1c33:06 = "<< this->GetEthercatConfig()->GetSlave(slave_name)->GetTelemetrySDOEntry("Calc and copy time 1")->LoadValue() + 0<< "\t"
        << "0x1c33:09 = "<< this->GetEthercatConfig()->GetSlave(slave_name)->GetTelemetrySDOEntry("Delay time 1")->LoadValue() + 0<< "\t";
    std::cout << std::endl;

    if(this->wire_sensor) wire_sensor->Update();
    SubsystemContentCreator<KVFilterDriveContext, KVFilterDriveTask, KVFilterDrive, KVFilterDriveTelemetry>::Action(); 
}

KVFilterDrive::Properties KVFilterDrive::GetProperties()
{
    return this->props;
}

void KVFilterDrive::RegisterWireSensor(WireSensor* sensor)
{
    this->wire_sensor = sensor;
}

void KVFilterDrive::RegisterDrive(EthercatSlave* drive)
{
    this->drive = drive;
}

EthercatSlave* KVFilterDrive::GetDrive()
{
    return this->drive;
}