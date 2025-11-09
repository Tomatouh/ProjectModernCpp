export module board;

import peon;
#include "Money.h"

export class board {
private:
    int zone{0};
    peon playerPeon;
public:
    explicit board(int initialZone) noexcept : zone{initialZone} {}

    void checkZone() noexcept {}

    int getZone() const noexcept { return zone; }
    void setZone(int newZone) noexcept { zone = newZone; }
};