export module card;
import <iostream>;
import <vector>;
import <string>;
import <unordered_set>;
import <string_view>;
#include "BuildingResource.h"

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
			std::vector<ResourceType> getResources() const;
			std::uint16_t getCoins() const;
		};

		Card(const std::vector<Effect>& effects, const Cost& cost, std::string_view name);
		Card(const Card& other);
		Card(Card&& other);
		Card& operator=(const Card& other);
		Card& operator=(Card&& other);

	private:
		std::vector<Effect> m_effects;
		Cost m_cost;
		std::string m_name;
		
};
	
}