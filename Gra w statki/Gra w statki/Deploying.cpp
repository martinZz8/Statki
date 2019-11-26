#include "Deploying.h"

Deploying::Deploying(Utils& utils, Board& board1, Board& board2):windowID(WINDOW_DEPLOYING), u(utils), b1(board1), b2(board2)
{
	play_sample_guard = true;
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
	if (u.getMouse1Clicked()==true && play_sample_guard==true)
	{
		u.playSample(AUDIO_PLACED_SHIP);
		play_sample_guard = false;
	}
	else if (u.getMouse1Clicked()==false) //kiedy puscimy przycisk myszy mozna bedzie znowu odtworzyc sampla
	{
		play_sample_guard = true;
	}
}

int Deploying::getWindowID()
{
	return windowID;
}