#pragma once
#include "GameObject.h"

/**
* Lasers shot from the player ship, moving up the screen
* child of GameObject class
*/

class PlayerLaser : public GameObject
{
public:
	PlayerLaser(int x, int y); // constructor
	void restart(int x, int y);
	void move();
};
