export module effects;
import Building;
import card;
import Player;
import board;

export void addCoins(Player& player, const Card& card);
export void addVictorypoints(Player& player, const Card& card);
export void addResources(Player& player, const Building& card);
//export void addShields(bool player, Board& board);
export void addScientificSymbol(Player& player, const Building& card);