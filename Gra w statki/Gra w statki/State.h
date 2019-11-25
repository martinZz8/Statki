#pragma once

class State
{

public:
	State() {};
	~State() {};
	virtual void tick() = 0;
	virtual void render(float mouse_x, float mouse_y) = 0;
	virtual int getWindowID() = 0;
};

