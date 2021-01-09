#pragma once
#include "GameObject.h"

/**
* the Enemy moves across the screen
* child of GameObject class
*/
class Enemy : public GameObject
{
public:
	Enemy();
	void move();
private:
	bool direction; // true = move toward the right, false = move toward the left
};