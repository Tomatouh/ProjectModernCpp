export module board;
import <cstdint>;
export class Board {
private:
private:
    int const static startPos = 0;

    int pos = startPos;
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
public:
    void incrementPos() noexcept { ++pos; }
    void decrementPos() noexcept { --pos; }
    [[nodiscard]] int getPos() const noexcept { return pos; }
    void setPos(int newPos) noexcept { pos = newPos; }
    explicit Board(int initialZone) noexcept : zone{initialZone} {}

    void checkZone(bool Player);

    void move(uint8_t steps, bool player) noexcept(false);
    int getZone() const noexcept { return zone; }
    void setZone(int newZone) noexcept { zone = newZone; }
};
