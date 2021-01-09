#pragma once
#include "GameObject.h"

/**
* Lasers coming down from enemies
* child of GameObject class
*/
class EnemyLaser : public GameObject
{
public:
	EnemyLaser(int x, int y); // constructor
	void restart(int x, int y);  // revive a laser
	void move();
};