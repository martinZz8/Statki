#define _CRT_SECURE_NO_WARNINGS
#include "Button.h"

Button::Button(Utils& utils, string text, float width, float height, float x, float y, float text_x_offset, float text_y_offset, bool choosed, int button_ID):u(utils), width(width), height(height), x(x), y(y), text_x_offset(text_x_offset), text_y_offset(text_y_offset),choosed(choosed), button_ID(button_ID)
{
	this->text = text;
	activated = false;
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

void Button::setChoosed(bool h)
{
	choosed = h;
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

bool Button::getChoosed()
{
	return choosed;
}

int Button::getButtonID()
{
	return button_ID;
}

void Button::paintButtonWithText(int size)
{
	if(activated == false && choosed == false)
		al_draw_filled_rectangle(x, y, x + width, y + height, u.color(39, 55, 106));
	else
		al_draw_filled_rectangle(x, y, x + width, y + height, u.color(30, 31, 41));
	u.drawText(text.c_str(), size, 183, 234, 243, x + text_x_offset, y + text_y_offset);
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