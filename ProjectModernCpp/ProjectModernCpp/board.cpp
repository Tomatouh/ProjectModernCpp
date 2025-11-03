import board;


void board::checkZone()
{
	int pos = PlayerPeon.getPos();
	if ( == 0) return; 
	if (pos <= 2 && pos >= 1) { zone = 1; }
	else if (pos >= 3 && pos <= 5) { zone = 2; }
	else if (pos >= 6 && pos <= 8) { zone = 3; }
	else zone = -1;
}
