export module card;
import <iostream>;
import <vector>;
import <string>;
import <unordered_set>;
import <string_view>;
#include "BuildingResource.h"

	export class Card {
	public:
		enum class Effect {
			addRawMaterial,
			addManufacturedGood,
			addEveryRawMaterial,
			addEveryManufacturedGood,
			addCoins,
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
			Cost() = default;
			Cost(const std::vector<ResourceType>& resources, std::uint16_t coins);
			~Cost() = default;
			std::vector<ResourceType> getResources() const;
			std::uint16_t getCoins() const;
		};
		

		Card(const std::vector<Effect>& effects, const Cost& cost, std::string_view name, std::uint8_t id);
		Card(const Card& other);
		Card(Card&& other) noexcept;
		Card& operator=(const Card& other);
		Card& operator=(Card&& other) noexcept;
		~Card() = default;

		void swap(Card& other) noexcept;


	private:
		std::vector<Effect> m_effects;
		Cost m_cost;
		std::string m_name;
		std::uint8_t m_id;
		
};
	
