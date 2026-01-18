#include "Checker.h"
import game;
import Player;
//import cardsLoader;
import card;
import board;
import std;
import <iostream>;
import <vector>;

int main() {
	
	if (checkSystemCompatibility() == true)
	{
		Game game;
		game.run();
	}
	else
		std::cout << "Your system does not meet the minimum requirements to play this game.";
	return 0;
}