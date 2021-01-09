#include "Game.h"
#include <conio.h>

//### TODO METHODS

void Game::createPlayerLaser()
{
	//### TODO	
	playerLasers[0] = new PlayerLaser(player.position.X, player.position.Y - 1);
	playerLasersCount = 1;
}

void Game::moveAllEnemyLasers()
{
	//### TODO	
	for (int i = 0; i < enemiesCount; i++)
	{
		//Sleep(1000);
		enemyLasers[i] = new EnemyLaser(enemies[i]->position.X, enemies[i]->position.Y + 1);
		if (enemyLasers[i]->isAlive)
		{
			enemyLasers[i]->move(); 
		}
	}
}

bool Game::checkPlayerKilled()
{
	//### TODO	
	return false;
}

void Game::moveAllPlayerLasers()
{
	//### TODO
	for (int i = 0; i < playerLasersCount; i++)
	{
		if (playerLasers[i]->isAlive)
		{
			playerLasers[i]->move();
		}
	}
}

void Game::createEnemyLaser(int x, int y)
{
	EnemyLaser* enemyLaser = new EnemyLaser(x,y);

	/*while (position.X < (ui.getHeight() - 3) && ui.checkChar(bullet.getX(), (bullet.getY() + 1)) != '*')
	{
		if (ui.checkChar(bullet.getX(), (bullet.getY() + 1)) != '*')
		{
			int previous = ui.drawChar(bullet.getX(), bullet.getY(), ' ', 'y');
		}

		if (ui.checkChar(bullet.getX(), (bullet.getY() + 1)) == '^')
		{
			gameOver();
			break;
		}

		int newpos = ui.drawChar(bullet.getX(), (bullet.getY() + 1), '|', 'y');
		bullet.setY(newpos);
		Sleep(75);
	}
	int final = ui.drawChar(bullet.getX(), bullet.getY(), ' ', 'y');*/
}

void Game::moveAllEnemies()
{
	//### TODO

	for (int i = 0; i < enemiesCount; i++)
	{
		if (enemies[i]->isAlive)
		{
			enemies[i]->move();
		}
	}
}

void Game::checkEnemiesKilled()
{
	//### TODO
}

void Game::createEnemies()
{
	clock_t t;

	t = clock() - lastNewEnemyTime;
	if ((((float)t) / CLOCKS_PER_SEC) > secondsPerNewEnemy)
	{
		lastNewEnemyTime = clock();
		//### TODO	
	}
}

int Game::getAliveEnemiesCount()
{
	//### TODO
	return 1;// none were ever created, so don't return 0
}

bool Game::checkAllEnemiesKilled()
{
	//### TODO	
	return false;
}


//*****************************************************************8
// Constructor
Game::Game()
{
	// initialize game variables
	score = 0;
	level = 1;
	playerLasersCount = 0;
	enemyLasersCount = 0;
	enemiesCount = 0;
	secondsPerNewEnemy = 5;// seconds
}

// Destructor
Game::~Game()
{
	// delete the enemies
	for (int i = 1; i <= enemiesCount; i++)
	{
		delete enemies[i - 1];
	}

	// delete the player lasers
	for (int i = 1; i <= playerLasersCount; i++)
	{
		delete playerLasers[i - 1];
	}

	// delete the enemy lasers
	for (int i = 1; i <= enemyLasersCount; i++)
	{
		delete enemyLasers[i - 1];
	}
}

int Game::getScore()
{
	return score;
}

int Game::getLevel()
{
	return level;
}

// Play() method starts and ends the game
// return: 0=>Game Over, 1=>You win, 2=>You Quit
// type e to quit/exit game
int Game::play()
{
	char KeyPressed; // key pressed by player on keyboard

	// set window dimension 100 columns, 42 lines
	system("CLS");
	UIKit::setWindowDimensions(0, 0, 100, 42);

	// left game frame with player ship etc... 
	// the game field is 40 columns X 40 lines
	// so make the frame around 41 columns, 43 lines, color 15
	UIKit::frame(0, 0, 41, 42, 15);

	// right frame for level display, color 11
	UIKit::frame(49, 4, 70, 6, 11);

	// right frame for score display, color 11
	UIKit::frame(49, 6, 70, 8, 11);

	// show the player ship
	player.show();

	// create at least 1 ET (Enemy), those move from left to right
	enemies[0] = new Enemy;
	enemiesCount = 1;
	createEnemyLaser(enemies[0]->position.X, enemies[0]->position.Y + 1);
	lastNewEnemyTime = clock();// time when the last ennemy was created

	gamePaused = false;

	// MASTER GAME LOOP
	while (true)
	{
		Sleep(100); // slow down the game loop

		//Read keyboard input
		if (_kbhit())
		{
			KeyPressed = _getch();
		}
		else
		{
			KeyPressed = 0;
		}

		if (KeyPressed == 'h')
		{
			// pause the game
			gamePaused = true;
			continue; // skip the rest and restart from top of while loop
		}
		else if (KeyPressed == 0 and gamePaused)
		{
			// no key pressed, stay paused
			continue; // skip the rest and restart from top of while loop
		}
		else
		{
			// key was pressed, resume game
			gamePaused = false;
		}

		switch (KeyPressed)
		{
		case 'e':
			return 2;// User quit the game before the end

		case 32:
			// spacebar ASCII code = 32
			// Create new player ship lasers
			// ### TODO
			createPlayerLaser();
			break;

		case 'k':
		case 'l':
			// Move player ship
			player.move(KeyPressed);
			break;
		}
		// end of switch


		// move the enemy lasers
		// ### TODO
		moveAllEnemyLasers();

		// check if player ship killed by enemy fire 
		// ### TODO
		if (checkPlayerKilled())
			return 0;// game over

		// move the player ship lasers 
		// ### TODO
		moveAllPlayerLasers();

		// move the enemies
		// ### TODO
		moveAllEnemies();
		
		// check any enemies killed
		// ### TODO
		checkEnemiesKilled();

		// count how many enemies are alive
		// stop game if 15 enemies alive (as per problem requirement)
		// ### TODO
		if (getAliveEnemiesCount() >= 15)
		{
			return 0; // Game Over
		}

		// Check if all enemies were killed
		// End game or change level
		// ### TODO
		if (checkAllEnemiesKilled())
		{
			return 1; // you win
		}

		// periodically create more enemies
		// ### TODO 
		createEnemies();

		// Update game info in the right frame 
		UIKit::color(gameInfoColor);

		// level 
		UIKit::gotoXY(50, 5); // go in level box
		std::cout << "Level    : " << level;

		// score
		UIKit::gotoXY(50, 7); // go in score box
		std::cout << "Score    : " << score;
	}
}
