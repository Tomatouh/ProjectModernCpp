export module Player;
import <string>;

export class Player {
public:
	std::string name;
	int score;

	Player(const std::string& n);
};