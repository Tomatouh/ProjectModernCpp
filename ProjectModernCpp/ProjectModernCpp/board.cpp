module board;
import peon;

void Board::checkZone(bool Player)
{
	int pos = playerPeon.getPos();
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
