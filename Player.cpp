#include "Player.h"

using namespace std;

// Constructor
Player::Player()
	:GameObject(18,11,20,40,0)
{
	// Display the Player ASCII code 18
	// color = 11 jade, high intensity
	// X=20 initial position column 20;
	// Y=40 ship always on line 40
	// 0 POINTS_ON_DEATH when killed
	show();
}

// overloading copy contructor
Player::Player(const Player& p) 
	:GameObject(18, 10, 15, 40, 0)
{ 
	// x=15 instead of 20
	// color 10 green instead of 11
}

void Player::move()
{
	// just because it is required by the parent class, should not be used
	cout << "Error in Ship class, method move() called";
}

void Player::move(char keypressed)
{
	// ship can move between column 1 and 40
	switch (keypressed)
	{
	case 'l':
		if (position.X < 40)
		{
			moveTo(position.X+1, position.Y); // move right
		}
		break;
	case 'k':
		if (position.X > 1)
		{
			moveTo(position.X - 1, position.Y); // move left
		}
		break;
	}
}










