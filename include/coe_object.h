/**
 * @brief Basic class. Contains CoE object properties and methods.
 * @warning Must NOT be created by user!
 * @see PDOEntriesList, SDOList.
*/

#ifndef COE_OBJECT_H
#define COE_OBJECT_H

#include <string>
#include "ecrt.h"

class CoEObject
{
	std::string name {""};
	uint16_t index {0};
	uint8_t subindex {0};
	uint16_t size{0};
	int64_t value{0};

	uint8_t* domain_offset;
	uint16_t byte_position;
	uint8_t bit_position;

public:
	/**
	 * @brief Sets object data.
	 * @param[in] name Object's name.
	 * @param[in] index Object's index.
	 * @param[in] subindex Object's subindex.
	 * @param[in] size Object's value size in bits.
	*/
	CoEObject(std::string name, uint16_t index, uint8_t subindex, uint16_t size);
	/**
	 * @brief Gets object's name.
	 * @returns Object's name.
	*/
	std::string GetName();
	/**
	 * @brief Gets object's index.
	 * @returns Object's index.
	*/	
	uint16_t GetIndex();
	/**
	 * @brief Gets object's subindex.
	 * @returns Object's subindex.
	*/	
	uint8_t GetSubindex();
	/**
	 * @brief Gets object's size in bits.
	 * @returns Object's size in bits.
	*/	
	uint8_t GetSizeBit();
	/**
	 * @brief Sets domain offset.
	 * @param[in] domain_offset Domain offset.
	*/
	void RegisterDomainOffset(uint8_t* domain_offset);
	/**
	 * @brief Sets byte positon.
	 * @param[in] byte_position Byte position.
	*/
	void RegisterBytePosition(uint16_t byte_position);
	/**
	 * @brief Sets bit positon.
	 * @param[in] byte_position Bit position.
	*/
	void RegisterBitPosition(uint8_t bit_position);
	/**
	 * @brief Gets actual value.
	 * @returns Actual object's value.
	*/
	int64_t LoadValue();
	/**
	 * @brief Sets actual value (for RW objects only).
	 * @param[in] value Required value.
	*/
	void StoreValue(int64_t value);
	/**
	 * @brief Writes stored value to ethercat domain.
	 * @warning This method calles in the end of each cycle
	 * in EthercatSlavesContainer::WriteProcessDataToDomain();
	 * @see EthercatSlavesContainer::WriteProcessDataToDomain();
	*/
	void WriteValueToFrame(); 
	/**
	 * @brief Reads value to ethercat domain.
	 * @warning This method calles in the begining of each cycle
	 * in EthercatSlavesContainer::ReadProcessDataFromDomain();
	 * @see EthercatSlavesContainer::ReadProcessDataFromDomain();
	*/
	void ReadValueFromFrame();	
	/**
	 * @brief Gets value address.
	 * @returns Value address.
	*/
	int64_t* GetValueAddress();

protected:
	int64_t ec_read_le(uint8_t* pBitsArray, uint16_t bytePos, uint8_t bitPos, uint8_t qBits);
	void ec_write_le(uint8_t* pBitsArray, uint16_t bytePos, uint8_t bitPos, int64_t data, uint8_t qBits);
};

#endif