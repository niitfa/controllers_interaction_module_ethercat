/**
 * @brief Derived from CoEObject. Used in slave's PDOs. 
 * @warning Must NOT be created by user!
 * @see CoEObject
*/

#ifndef COE_PROCESS_OBJECT_H
#define COE_PROCESS_OBJECT_H

#include <string>
#include "coe_object.h"

class CoEProcessObject : public CoEObject
{
public:
	/**
	 * @brief Sets object data.
	 * @param[in] name Object's name.
	 * @param[in] index Object's index.
	 * @param[in] subindex Object's subindex.
	 * @param[in] size Object's value size in bits.
	*/
	CoEProcessObject(std::string name, uint16_t index, uint8_t subindex, uint16_t size);
};

#endif