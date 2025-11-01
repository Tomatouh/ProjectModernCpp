export module card;
import <iostream>;
#include "BuildingResource.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <string_view>

namespace SevenWonders {
	export class Card {
	public:
		enum class Effect {
			addRawMaterial,
			addManufacturedGood,
			/*addClay,
			addWood,
			addStone,
			addGlass,
			addPapyrus,*/
			addEveryRawMaterial,
			addEveryManufacturedGood,
			addVictoryPoints,
			addShields,
			oneCoinClay,
			oneCoinWood,
			oneCoinStone,
			oneCoinGlass,
			oneCoinPapyrus
		};

		class Cost {
		private:
			std::vector<ResourceType> m_resources;
			std::uint16_t m_coins;
		public:
			Cost(const std::vector<ResourceType>& resources, std::uint16_t coins);
		};

		Card(const std::vector<Effect>& effects, const Cost& cost, std::string_view name);
		Card(const Card& other);

	private:
		std::vector<Effect> m_effects;
		Cost m_cost;
		std::string m_name;
		//SevenWonders::Card* m_link;
};
	
}