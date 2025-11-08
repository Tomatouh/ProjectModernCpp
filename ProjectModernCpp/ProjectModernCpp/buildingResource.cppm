export module buildingResource;
import resource;
export enum class ResourceType {
	WOOD,
	STONE,
	CLAY,
	GLASS,
	PAPYRUS
};
export class BuildingResource :public Resource
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