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
			std::uint8_t m_link;
			std::vector<ResourceType> m_resources;
			std::uint8_t m_coins;
		public:
			Cost() = default;
			Cost(std::uint8_t link, const std::vector<ResourceType>& resources, std::uint8_t coins);
			~Cost() = default;
			std::uint8_t getLink() const;
			std::vector<ResourceType> getResources() const;
			std::uint8_t getCoins() const;

		};
		
		Card() = default;
		Card(const std::vector<Effect>& effects, const Cost& cost, std::string_view name, std::uint8_t id, 
			 std::uint8_t victoryPoints, std::uint8_t shields, std::uint8_t coins);
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
		std::uint8_t m_victoryPoints;
		std::uint8_t m_shields;
		std::uint8_t m_coins;
		
};
	
