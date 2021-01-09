#include "GameObject.h"
using namespace std;

GameObject::GameObject(int charCode, int colorCode, int x, int y, int pointsOnDeath)
	: CHAR_CODE(charCode), COLOR_CODE(colorCode), POINTS_ON_DEATH(pointsOnDeath)
{
	position.X = x; 
	position.Y = y; 
	isAlive = true;
}

void GameObject::moveTo(int x, int y)
{
	hide();
	position.X = x;
	position.Y = y;
	show();
}

int GameObject::kill()
{
	isAlive = false;
	hide();
	return POINTS_ON_DEATH;
}

void GameObject::hide() const
{
	UIKit::gotoXY(position.X, position.Y);
	cout << " ";
}

void GameObject::show() const
{
	UIKit::gotoXY(position.X, position.Y);
	UIKit::color(COLOR_CODE);
	cout << (char)(CHAR_CODE);
}

GameObject::~GameObject()
{ }
