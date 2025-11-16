import peon;
void peon::move(int steps, bool player) {
	if(steps < peon::startPos) {
		throw ("Steps cannot be negative");
	}
	else if(steps >peon::winPosP2) {
		throw ("Steps cannot be greater than 9");
	}
	if (player=false) {
		for (int i = 0; i < steps; ++i) {
			incrementPos();
		}
	} else {
		for (int i = 0; i < steps; ++i) {
			decrementPos();
		}
	}
}