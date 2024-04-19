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
	void AddEntry(std::string name, uint16_t index, uint8_t subindex, uint16_t size);
	std::map<std::string, CoEProcessObject*>* GetMap();
	uint16_t GetSize();
	CoEProcessObject* GetEntry(std::string name);
};

#endif