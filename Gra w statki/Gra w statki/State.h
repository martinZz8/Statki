#pragma once

class State
{

public:
	State() {};
	~State() {};
	virtual void tick() = 0;
	virtual void render() = 0;
	virtual int getWindowID() = 0;
};

