#include "PlayerLaser.h"

PlayerLaser::PlayerLaser(int x, int y)
	: GameObject(15, 9, x, y, 0)
{
	// ASCII code 15, 
	// ShipLaserColor = 9 blue color, high intensity
	show();
}

void PlayerLaser::restart(int x, int y)
{
	position.X = x;  // column where to start
	position.Y = y;   // row where to start
	isAlive = true;
	show();
}

void PlayerLaser::move()
{
	// ship lasers move up the screen
	// if not reached the top of the screen, move up
	if (position.Y > 1)
	{
		moveTo(position.X, position.Y - 1); // move up
	}
	// if laser reached top of screen kill hit
	else kill();
}