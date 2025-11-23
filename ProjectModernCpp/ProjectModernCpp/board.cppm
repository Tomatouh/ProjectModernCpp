export module board;

import peon;
export class Board {
private:
	int const static k_zone_start = 0;
	int const static k_zone_win = 9;
    int const static k_zone1_start = 1;
    int const static k_zone2_start = 3;
    int const static k_zone3_start = 6;
    int const static k_zone1 = 1;
    int const static k_zone2 = 2;
    int const static k_zone3 = 3;
    int const static militaryWinP2 = 4;
	int const static winPosP2 = -9;
	int const static winPosP1 = 9;
    int zone{k_zone_start};
    Peon playerPeon;
public:
    explicit Board(int initialZone) noexcept : zone{initialZone} {}

    void checkZone(bool Player) {}

    void move(int steps, bool player) noexcept(false);
    int getZone() const noexcept { return zone; }
    void setZone(int newZone) noexcept { zone = newZone; }
};

void Board::move(int steps, bool player) noexcept(false)
{
		if (steps < playerPeon.getPos()) {
			throw ("Steps cannot be negative");
		}
		else if (steps > winPosP2) {
			throw ("Steps cannot be greater than 9");
		}
		if (player == false) {
			for (int i = 0; i < steps; ++i) {
				playerPeon.incrementPos();
			}
		}
		else {
			for (int i = 0; i < steps; ++i) {
				playerPeon.decrementPos();
			}
		}
}
