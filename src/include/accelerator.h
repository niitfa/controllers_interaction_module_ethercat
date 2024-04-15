#ifndef ACCELERATOR_H
#define ACCELERATOR_H

#include "subsystem.h"

class Accelerator : public Subsystem
{
public:
	void Action() override;
};

#endif