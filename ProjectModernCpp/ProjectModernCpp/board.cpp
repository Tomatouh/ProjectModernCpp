module board;

void Board::checkZones()
{
	int pos =this->getPos();
	if ( pos == Board::k_zone_start) return; 
	if (pos>0) {
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


void Board::move(const  int & steps) noexcept(false)
{
	if (steps <0) {
		for (int i = 0; i > steps; i--) {
			this->decrementPos();
		}
	}
	else if (steps > 0) {
		for (int i = 0; i < steps; ++i) {
			this->incrementPos();
		}
	}
	checkZones();
}
