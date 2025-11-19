import peon;
void Peon::move(int steps, bool player) {
	if(steps < Peon::startPos) {
		throw ("Steps cannot be negative");
	}
	else if(steps >Peon::winPosP2) {
		throw ("Steps cannot be greater than 9");
	}
	if (player==false) {
		for (int i = 0; i < steps; ++i) {
			incrementPos();
		}
	} else {
		for (int i = 0; i < steps; ++i) {
			decrementPos();
		}
	}
}