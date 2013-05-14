//
//  GO_Button.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-05-08.
//
//

#include "GO_Button.h"

GO_Button::GO_Button(vec3 pos) : GameObject(BoundingBox(0))
{
	loadModel("button.obj");
	addMaterial("button_c.tga", 1, 100);
	setPosition(pos);
}

std::string GO_Button::getType()
{
	return "button";
}

void GO_Button::setPressed(bool isPressed)
{
	_isPressed = isPressed;
}

bool GO_Button::getPressed()
{
	return _isPressed;
}
