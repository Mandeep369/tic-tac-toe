#pragma once
#include "UIKit.h"

/**
* Parent class for all game actors: player, lasers, enemies
* This is an abstract class: move() method must be implemented in all child classes
*/
class GameObject
{
public:
	COORD position;	// position on screen (see wincontypes.h)
	bool isAlive;	// if alive it can move and can be killed for POINTS_ON_DEATH

	// constructor
	GameObject(int charCode, int colorCode, int x, int y, int pointsOnDeath);
	~GameObject();				// destructor

	// public methods
	void show() const;			// display the character
	int kill();
	virtual void move() = 0;	// pure virtual->all child classes must implement

protected:
	const int CHAR_CODE;			// ASCII character to display
	const int COLOR_CODE;		// color of the character
	const int POINTS_ON_DEATH;			// number of POINTS_ON_DEATH when killed
	void moveTo(int x, int y);	// move to a new position
	void hide() const;			// erase the character
};

