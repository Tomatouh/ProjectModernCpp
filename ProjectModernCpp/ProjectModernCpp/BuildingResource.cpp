module buildingResource;
void BuildingResource::add()
{
	m_value++;
}
uint8_t BuildingResource::getValue() const
{
	return m_value+m_temporaryValue;
}
ResourceType BuildingResource::getType() const
{
	return m_type;
}
BuildingResource::BuildingResource(const ResourceType& type) {
	this->m_type = type;
	this->m_value = 0;
	this->m_temporaryValue = 0;
}