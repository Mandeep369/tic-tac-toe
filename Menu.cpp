//implementation of the menu class
#include "Menu.h"

Menu::Menu(string title, string* choiceList, int itemsCount, int startLine, int startColumn)
{
	this->title=title;
	this->choiceList = new string[itemsCount];
	for(int i=0;i<itemsCount;i++)
	{
		this->choiceList[i]=choiceList[i];
	}
	choiceList;
	this->itemsCount= itemsCount;
	this->topLeftCornerPosition.X= startColumn;
	this->topLeftCornerPosition.Y= startLine;
	//initializing the positions
	init();
}

Menu::~Menu()
{
	delete[] this->choiceList;
}

void Menu::init()
{
	//initialization of the positions and the choice
	this->choice=1;
	this->currentPosition.X = topLeftCornerPosition.X;
	this->currentPosition.Y = topLeftCornerPosition.Y+2;
	this->initialPosition= currentPosition;
	this->previousPosition= initialPosition;
	this->previousPosition.Y= initialPosition.Y+2*(itemsCount-1);
}

int Menu::displayMenu()
{
	COORD nextPosition = currentPosition;
	//draw the menu
	gotoXY(topLeftCornerPosition);
	cout << title << endl;
	for(int i = 0; i < itemsCount; i++)
	{
		gotoXY(topLeftCornerPosition.X+4, initialPosition.Y+(2*i));
		cout << choiceList[i] << endl;
	}
	//get arrow input
	int key;
	//move(currentPosition, initialPosition);
	move(currentPosition, currentPosition);
	do
	{	
		nextPosition=currentPosition;
		key =_getch();
		if(key == 224)
		{
			key = _getch();
		}
		//move
		switch(key)
		{
		case 80:	//down key
			if(currentPosition.Y == previousPosition.Y) //if we are already down
			{
				move(currentPosition, initialPosition);
				currentPosition = initialPosition;
				choice = 1;
			}
			else
			{
				nextPosition.Y += 2;
				move(currentPosition, nextPosition);
				currentPosition.Y += 2;
				choice++;
			}
			break;	
		case 72:	//up key
			if(currentPosition.Y == initialPosition.Y) //if we are already up
			{
				move(currentPosition,previousPosition);
				currentPosition = previousPosition;
				choice = itemsCount;
			}
			else
			{
				nextPosition.Y -= 2;
				move(currentPosition, nextPosition);
				currentPosition.Y -= 2;
				choice--;
			}
			break;
		}

	}
	while(key !=13);

	//return the choice
	return choice;
}

void Menu::move(COORD origin, COORD target)
{
	//erase
	gotoXY(origin);
	cout << "   " << endl;
	//draw
	gotoXY(target);
	cout << "-->" << endl;
}

int Menu::getMaxSize()
{
	return 0;
}

void Menu::gotoXY(COORD pos)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void Menu::gotoXY(int c, int l)
{
	COORD position;
	position.X=c;
	position.Y=l;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),position);
}
