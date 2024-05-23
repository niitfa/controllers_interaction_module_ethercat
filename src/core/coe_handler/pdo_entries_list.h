/**
 * @brief Contains CoE objects used as PDO. Used for passing in 
 * EthercatSlave while user thread configuring.
 * @details Configuration example:
 * @code
 * #include "pdo_entries_list.h"
 * #include "coe_object_names.h"
 * 
 * void ConfigurePDO()
 * {
 *		// Values coe_object_names::kObjectName1...4 should be
 * 		// previously defined in coe_object_names namespace.
 * 		// Using other std::string values as CoE object names is
 * 		// not recommended.
 * 
 * 		PDOEntriesList* rxpdo = new PDOEntriesList();
 * 		rxpdo->AddEntry(coe_object_names::kObjectName1, 0x7001, 0x00, 16);
 * 		rxpdo->AddEntry(coe_object_names::kObjectName2, 0x7002, 0x01, 8);
 * 
 * 		PDOEntriesList* txpdo = new PDOEntriesList();
 * 		txpdo->AddEntry(coe_object_names::kObjectName3, 0x6010, 0x00, 32);
 * 		txpdo->AddEntry(coe_object_names::kObjectName4, 0x6020, 0x00, 32);
 * }
 * 
 * @endcode
*/

#ifndef PDO_ENTRIES_LIST_H
#define PDO_ENTRIES_LIST_H

#include <map>
#include "coe_process_object.h"

class PDOEntriesList
{
	std::map<std::string, CoEProcessObject*> pdo_entries;
public:
	PDOEntriesList() = default;
	~PDOEntriesList();
	/**
	 * @brief Adds PDO entry.
	 * @param[in] name Object's name.
	 * @param[in] index Object's index.
	 * @param[in] subindex Object's subindex.
	 * @param[in] size Object's value size in bits.
	*/
	void AddEntry(std::string name, uint16_t index, uint8_t subindex, uint16_t size);
	/**
	 * @brief Provides direct access to PDO map.
	 * @returns Pointer to PDO map.
	 * @warning Must NOT be called by user!
	*/
	std::map<std::string, CoEProcessObject*>* GetMap();
	/**
	 * @brief Gets size of PDO map.
	 * @returns Size of PDO map.
	*/
	uint16_t GetSize();
	/**
	 * @brief Finds CoEObject by name and gets it's pointer.
	 * @param[in] name Object's name.
	 * @returns Pointer to CoE object with given name if it exists in list, otherwise returns nullptr.
	 * @warning Must NOT be called by user!
	*/
	CoEProcessObject* GetEntry(std::string name);
	void MergeWith(PDOEntriesList* other);
};

#endif