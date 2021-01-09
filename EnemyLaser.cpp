#include "EnemyLaser.h"

EnemyLaser::EnemyLaser(int x, int y)
	:GameObject(33, 10,x,y,0)
{
	// character 33
	// color = 10 green color, high intensity
	show();
}

void EnemyLaser::restart(int x, int y)
{
	position.X = x;  // column where to start
	position.Y = y;  // row where to start
	isAlive = true;
	show();
}

void EnemyLaser::move()
{
	// enemy lasers move down the screen
	// if not reached the bottom of the screen, move down
	if (position.Y < 41)
	{
		moveTo(position.X, position.Y + 1); // move down
	}
	// if laser reached bottom of screen kill hit
	else kill();
}