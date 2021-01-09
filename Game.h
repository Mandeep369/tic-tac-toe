#pragma once
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include "Player.h"
#include "PlayerLaser.h"
#include "Enemy.h"
#include "EnemyLaser.h"

class Game
{
public:
	int play(); // returns: 0 => Game over, 1 => You win, 2 => You quit
	int getScore();
	int getLevel();
	Game(); //constructor
	~Game(); //destructor

private:
	int score;
	int level; // use if doing multiple levels
	bool gamePaused;

	// game color
	const int gameInfoColor = 15; // white

	// the player ship
	Player player;

	// player lasers array
	const int maxPlayerLasersCount = 50;
	int playerLasersCount; // current number in array
	PlayerLaser* playerLasers[50]; // array of pointers

	// enemy array
	Enemy* enemies[10];// array of pointers
	int enemiesCount; // current number in array
	int secondsPerNewEnemy;// create a new enemy every x seconds
	clock_t lastNewEnemyTime; // time when the last enemy was created

	// enemy lasers array
	const int maxEnemyLasersCount = 20;
	int enemyLasersCount; // current number in array
	EnemyLaser* enemyLasers[20]; // array of pointers

	// ### TODO: these method implementation in Game.cpp
	
	void createPlayerLaser();
	void createEnemies();
	void createEnemyLaser(int x, int y);
	
	void moveAllPlayerLasers();
	void moveAllEnemies();
	void moveAllEnemyLasers();

	bool checkPlayerKilled();
	void checkEnemiesKilled();
	bool checkAllEnemiesKilled();
	int getAliveEnemiesCount();
};

