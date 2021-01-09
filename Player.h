#pragma once

#include "UIKit.h"
#include "GameObject.h"

/**
* The ship at the bottom of the screen
* child of GameObject class
*/
class Player : public GameObject
{
public:
	Player();
	Player(const Player& p); // overloading copy contructor

	void move(char keypressed); // k move right, l move left
	void move(); // just because it is required, won't be used
};
