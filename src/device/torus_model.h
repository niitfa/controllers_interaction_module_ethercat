#ifndef TORUS_MODEL_H
#define TORUS_MODEL_H

#include "device_model.h"
#include "gantry.h"
#include "accelerator.h"

class TorusModel : public DeviceModel
{
	Gantry* gantry;
	Accelerator* accelerator;
public:
	TorusModel();
	~TorusModel();

	void RegisterGantry(Gantry* g);
	void RegisterAccelerator(Accelerator* acc);

	Gantry* GetGantry()	const;
	Accelerator* GetAccelerator() const;
};

#endif