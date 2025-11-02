#pragma once
#include "Resource.h"
enum class ResourceType {
	WOOD,
	STONE,
	CLAY,
	GLASS,
	PAPYRUS
};
class BuildingResource:public Resource
{
private:
	uint8_t m_value;
	ResourceType m_type;
	uint8_t m_temporaryValue;/*this stores traded resources*/
public:
	void add();
	uint8_t getValue() const;
	ResourceType getType() const;
	BuildingResource(const ResourceType& resourceType);
};

