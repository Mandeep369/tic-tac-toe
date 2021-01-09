#include "Enemy.h"

// constructor
Enemy::Enemy()
	: GameObject(43, 12, 0, 0, 50)
{
	// Display ASCII character code 43, color code 12
	// 50 POINTS_ON_DEATH when killed
	position.X = rand() % 40 + 1; // randomly set the initial position
	position.Y = rand() % 20 + 1;
	direction = true;
	show();
}

// move method
void Enemy::move()
{
	if (direction)
	{
		// move toward the right
		moveTo(position.X + 1, position.Y); // move right
		if (position.X == 40)
		{
			// change direction
			direction = false;
		}
	}
	else
	{
		// move toward the left
		moveTo(position.X - 1, position.Y); // left
		if (position.X == 1)
		{
			// change direction
			direction = true;
		}
	}
}