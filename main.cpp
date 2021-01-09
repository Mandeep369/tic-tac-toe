#include <iostream>
#include "UIKit.h"
#include "Menu.h"
#include "Game.h"
using namespace std;

void help()
{
	system("CLS");
	UIKit::color(11);
	UIKit::gotoXY(50, 10);
	cout << "k -> move left" << endl;
	UIKit::gotoXY(50, 11);
	cout << "l -> move right" << endl;
	UIKit::gotoXY(50, 12);
	cout << "spacebar -> shoot" << endl;
	UIKit::gotoXY(50, 13);
	cout << "h -> pause the game" << endl;
	UIKit::gotoXY(50, 14);
	cout << "e -> exit game" << endl;
	UIKit::gotoXY(50, 15);
	cout << "Kill all enemies to win" << endl;
	system("pause");
	return;
}

void playGame()
{
	// play the game
	Game newGame = Game();

	int gameResult;
	gameResult = newGame.play();

	// ### TODO Better display after game
	//
	system("CLS");
	UIKit::frame(48, 8, 70, 20, 2);
	UIKit::color(11);
	UIKit::gotoXY(50, 10);
	cout << "Your score = " << newGame.getScore() << endl;
	UIKit::gotoXY(50, 11);
	cout << "Your level = " << newGame.getLevel() << endl;

	UIKit::gotoXY(50, 13);

	switch (gameResult)
	{
	case 0:
		cout << "Game over! " << endl;
		break;
	case 1:
		cout << "You win!" << endl;
		break;
	case 2:
		cout << "You quit!" << endl;
		break;
	}
	system("pause");
}

int main()
{
	int selection;

	// Create main menu, 3 items, top left corner on line 5, column 8;
	// see Menu.h
	string choices[] = { "Play", "Help", "Exit" };
	Menu mainMenu = Menu("Welcome to Space Invaders!", choices, 3, 5, 50);

	while(true)
	{
		system("CLS");
		selection = mainMenu.displayMenu();
		
		switch (selection)
		{
		case 1:
			playGame();
			break;
			
		case 2:
			// display help
			help();
			break;

		case 3:
			// end program
			exit(0);
		}
	}
	return 0;
}