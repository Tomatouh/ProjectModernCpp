import game;
import Player;
//import cardsLoader;
import card;
import board;
import std;
import <iostream>;
import <vector>;

//import <memory>;

/*
* ID's : brown cards 1-9(1-3 wood, 4-6 clay, 7-9 stone)
*		 gray cards 10-13(10-11 glass, 12-13 papyrus)
*        red cards 14-27(14-19 1 shield, additionally grouped by linking, 20-25 2 shields, additionally grouped by linking, 26-27 3 shields)
*		 green cards 28-39(grouped by symbols and links(except school->university and lab->observatory)): 28-29 feathers,30-31 bowl, 32-33 triangle, 34-35 globe, 36-37 wheel, 38=39 book;
*		 yellow cards 40-52: 40-43 fix trading rules to 1 coin, 44-45 elective resources, 46-47 the ones that give fixed coins, 48 arena, 49-52 cash per building type yellow/red/gray/brown
*		 blue cards 53-66: grouped by amount of VP given ascendingly;
*		 guild cards 67-73;
*/
int main() {

	Game game;
	game.run();
	return 0;
}