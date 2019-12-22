#include "Button.h"

Button::Button(Utils& utils, float width, float height, float x, float y, bool activated, int button_ID):u(utils), width(width), height(height), x(x), y(y), activated(activated), button_ID(button_ID)
{
	highlighted = false;
}

void Button::setWidth(float width)
{
	this->width = width;
}

void Button::setHeight(float height)
{
	this->height = height;
}

void Button::setX(float x)
{
	this->x = x;
}

void Button::setY(float y)
{
	this->y = y;
}
void Button::setHighlighted(bool h)
{
	highlighted = h;
}

void Button::setActivated(bool h)
{
    activated = h;
}

float Button::getX()
{
	return x;
}

float Button::getY()
{
	return y;
}

float Button::getHeight()
{
	return height;
}

float Button::getWidth()
{
	return width;
}

bool Button::getHighlighted()
{
	return highlighted;
}

bool Button::getActivated()
{
	return activated;
}

int Button::getButtonID()
{
	return button_ID;
}

void Button::paintButtonWithText(const char* tekst, int size, float x_offset,float y_offset)
{
	if(activated == false)
		al_draw_filled_rectangle(x, y, x + width, y + height, u.color(39, 55, 106));
	else
		al_draw_filled_rectangle(x, y, x + width, y + height, u.color(30, 31, 41));
	u.drawText(tekst, size, 183, 234, 243, x + x_offset, y + y_offset);
}

void Button::paintButtonHighlight(int size)
{
	if(size==FONT_SIZE_SMALL)
		al_draw_rectangle(x, y, x + width, y + height, u.color(38, 179, 137),3);
	else if(size==FONT_SIZE_BIG)
		al_draw_rectangle(x, y, x + width, y + height, u.color(38, 179, 137), 5);
	else
		al_draw_rectangle(x, y, x + width, y + height, u.color(38, 179, 137), 15);
}