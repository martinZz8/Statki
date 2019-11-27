#include "Deploying.h"

Deploying::Deploying(Utils& utils, Board& board1, Board& board2):windowID(WINDOW_DEPLOYING), u(utils), b1(board1), b2(board2)
{
	deploy_ship_guard = true;
	resize_ship_guard = true;
	rotate_ship_guard = true;
}

//Deploying::Deploying():windowID(WINDOW_DEPLOYING)
//{
//	
//}

Deploying::~Deploying()
{

}

void Deploying::tick()
{
	b1.setFields();
	b2.setFields();
}

void Deploying::render()
{
	b1.paintBoard();
	b2.paintBoard();
	b1.paintStandardShip(u.getMouseX(), u.getMouseY());
	StandardKeyboardSwitches();
	MouseSwitches();
}

int Deploying::getWindowID()
{
	return windowID;
}

void Deploying::StandardKeyboardSwitches()
{
	if (u.getKeyUpPressed() == true && resize_ship_guard == true)
	{
		u.setShipSize(u.getShipSize() + 1);
		if (u.getShipSize() > 4)
			u.setShipSize(1);
		cout << "Rozmiar: " << u.getShipSize() << endl;
		resize_ship_guard = false;
	}
	if (u.getKeyDownPressed() == true && resize_ship_guard == true)
	{
		u.setShipSize(u.getShipSize() - 1);
		if (u.getShipSize() < 1)
			u.setShipSize(4);
		cout << "Rozmiar: " << u.getShipSize() << endl;
		resize_ship_guard = false;
	}
	if (u.getKeyUpPressed() == false && u.getKeyDownPressed() == false)
		resize_ship_guard = true;
	if (u.getKeyRightPressed() == true && rotate_ship_guard == true)
	{
		u.setShipOrientation(u.getShipOrientation() + 1);
		if (u.getShipOrientation() > 2)
			u.setShipOrientation(1);
		cout << "Orientacja: " << u.getShipOrientation() << endl;
		rotate_ship_guard = false;
	}
	if (u.getKeyLeftPressed() == true && rotate_ship_guard == true)
	{
		u.setShipOrientation(u.getShipOrientation() - 1);
		if (u.getShipOrientation() < 1)
			u.setShipOrientation(2);
		cout << "Orientacja: " << u.getShipOrientation() << endl;
		rotate_ship_guard = false;
	}
	if (u.getKeyRightPressed() == false && u.getKeyLeftPressed() == false)
		rotate_ship_guard = true;
}

void Deploying::MouseSwitches()
{
	if (u.getMouse1Clicked() == true && deploy_ship_guard == true)
	{
		u.playSample(AUDIO_PLACED_SHIP);
		deploy_ship_guard = false;
	}
	else if (u.getMouse1Clicked() == false) //kiedy puscimy przycisk myszy mozna bedzie znowu odtworzyc sampla
		deploy_ship_guard = true;
}