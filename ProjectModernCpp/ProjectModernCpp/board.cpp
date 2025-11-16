import board;
import peon;

void board::checkZone(bool Player)
{
	int pos = playerPeon.getPos();
	if ( pos == board::k_zone_start) return; 
	if (Player) {
		if (pos < board::k_zone2_start && pos >= board::k_zone1_start) { zone = board::k_zone1; }
		else if (pos >= board::k_zone2_start && pos < board::k_zone3_start) { zone = board::k_zone2; }
		else if (pos >= board::k_zone3_start && pos < board::k_zone_win) { zone = board::k_zone3; }
		else zone = board::militaryWinP2;
		return;
	}
    if (pos > -board::k_zone2_start && pos <= -board::k_zone1_start) {
        zone = -board::k_zone1;
    }
    else if (pos <= -board::k_zone2_start && pos > -board::k_zone3_start) {
        zone = -board::k_zone2;
    }
    else if (pos <= -board::k_zone3_start && pos > -board::k_zone_win) {
        zone =- board::k_zone3;
    }
    else {
        zone = -board::militaryWinP2;
    }
	return;
}
