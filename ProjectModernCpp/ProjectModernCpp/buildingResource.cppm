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
/*TO DO
calcul de rest(banca ofera rest mereu), cand se cere un anumit amount de la banca, calculeaza cate
monede da in fct de minimul de monede posibil cu ceea ce are, adica daca vrei 14 si nu ai monede de 6,
iti da 4 monede de 3 si 2 de 2, daca exista monede de 6 in banca iti da 2 monede de 6 si 2 monede de 2

trading rules sau whatever

si checkuri in trading rules pt trading rules custom de la guild cards
*/