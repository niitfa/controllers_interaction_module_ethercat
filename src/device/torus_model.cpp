#include "torus_model.h"

TorusModel::TorusModel() = default;

TorusModel::~TorusModel() = default;

void TorusModel::RegisterGantry(Gantry* g)
{
	this->DeviceModel::RegisterSubsystem(g, (Subsystem**)&gantry);
}

void TorusModel::RegisterAccelerator(Accelerator* acc)
{
	this->DeviceModel::RegisterSubsystem(acc, (Subsystem**)&accelerator);
}

Gantry* TorusModel::GetGantry() const
{
	return this->gantry;
}

Accelerator* TorusModel::GetAccelerator() const 
{
	return this->accelerator;
}