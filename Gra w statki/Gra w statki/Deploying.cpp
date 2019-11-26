#include "Deploying.h"

Deploying::Deploying(Utils& utils, Board& board1, Board& board2):windowID(WINDOW_DEPLOYING), u(utils), b1(board1), b2(board2)
{
	
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
	b1.paintShip(u.getMouseX(), u.getMouseY());
}

int Deploying::getWindowID()
{
	return windowID;
}