module board;

void Board::checkZone(bool Player)
{
	int pos =this->getPos();
	if ( pos == Board::k_zone_start) return; 
	if (Player) {
		if (pos < Board::k_zone2_start && pos >= Board::k_zone1_start) { zone = Board::k_zone1; }
		else if (pos >= Board::k_zone2_start && pos < Board::k_zone3_start) { zone = Board::k_zone2; }
		else if (pos >= Board::k_zone3_start && pos < Board::k_zone_win) { zone = Board::k_zone3; }
		else zone = Board::militaryWinP2;
		return;
	}
    if (pos > -Board::k_zone2_start && pos <= -Board::k_zone1_start) {
        zone = -Board::k_zone1;
    }
    else if (pos <= -Board::k_zone2_start && pos > -Board::k_zone3_start) {
        zone = -Board::k_zone2;
    }
    else if (pos <= -Board::k_zone3_start && pos > -Board::k_zone_win) {
        zone =- Board::k_zone3;
    }
    else {
        zone = -Board::militaryWinP2;
    }
	return;

}

void Board::move(uint8_t steps, bool player) noexcept(false)
{
	if (steps < this->getPos()) {
		throw ("Steps cannot be negative");
	}
	else if (steps > winPosP2) {
		throw ("Steps cannot be greater than 9");
	}
	if (player == false) {
		for (int i = 0; i < steps; ++i) {
			this->incrementPos();
		}
	}
	else {
		for (int i = 0; i < steps; ++i) {
			this->decrementPos();
		}
	}
}
