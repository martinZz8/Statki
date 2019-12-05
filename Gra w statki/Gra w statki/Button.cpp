#include "Button.h"

Button::Button(float width, float height, float x, float y, int button_ID):width(width), height(height), x(x), y(y), button_ID(button_ID)
{
	highlighted = false;
}

void Button::setHighlighted(bool h)
{
	highlighted = h;
}