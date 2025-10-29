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
	uint8_t value;
	ResourceType type;
public:
	void add1();
	uint8_t getValue() const;
	ResourceType getType() const;
};

