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

    int zone{k_zone_start};
    Peon playerPeon;
public:
    explicit Board(int initialZone) noexcept : zone{initialZone} {}

    void checkZone(bool Player) {}

    int getZone() const noexcept { return zone; }
    void setZone(int newZone) noexcept { zone = newZone; }
};