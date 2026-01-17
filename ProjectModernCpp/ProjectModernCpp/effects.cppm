export module effects;
import Building;
import card;
import Player;
import board; 
import std;



export void discardGrey(std::shared_ptr<Player> player);
export void discardBrown(std::shared_ptr<Player> player);
export std::uint16_t maxConstructedWonders(std::shared_ptr<Player> player);
export void drawProgress(std::shared_ptr<Player> player, std::vector< std::unique_ptr<Player::ProgressToken>>& m_progressTokensDeck);
//export void constructCard(std::shared_ptr<Player> player);