#include "pdo_entries_list.h"

PDOEntriesList::~PDOEntriesList()
{
	for (auto it = pdo_entries.begin(); it != pdo_entries.end(); ++it)     
	{
		if (it->second) delete it->second;
	}
}
void PDOEntriesList::AddEntry(std::string name, uint16_t index, uint8_t subindex, uint16_t size)
{
	CoEProcessObject* obj = new CoEProcessObject(name, index, subindex, size);
	pdo_entries.emplace(obj->GetName(), obj);
}

std::map<std::string, CoEProcessObject*>* PDOEntriesList::GetMap()
{
	return &this->pdo_entries;
}

uint16_t PDOEntriesList::GetSize()
{
	return this->pdo_entries.size();
}

CoEProcessObject* PDOEntriesList::GetEntry(std::string name)
{
	if(pdo_entries.find(name) != pdo_entries.end())
	{
		return pdo_entries.find(name)->second;
	}
	return nullptr;
}

void PDOEntriesList::MergeWith(PDOEntriesList* other)
{
	this->pdo_entries.insert(other->pdo_entries.begin(), other->pdo_entries.end());	
}