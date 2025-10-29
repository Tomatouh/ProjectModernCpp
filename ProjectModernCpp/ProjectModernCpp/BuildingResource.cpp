#include "BuildingResource.h"
void BuildingResource::add1()
{
	value++;
}
uint8_t BuildingResource::getValue() const
{
	return value;
}
ResourceType BuildingResource::getType() const
{
	return type;
}