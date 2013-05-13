//
//  Block.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-05-01.
//
//

#include "GO_Block.h"

GO_Block::GO_Block(vec3 pos) : GameObject(BoundingBox(0.5)), _oldPos(pos), _newPos(pos)
{
	loadModel("crate.obj");
	addMaterial("crate.tga", 1, 1);
	setPosition(pos);
}

std::string GO_Block::getType()
{
	return "block";
}

void GO_Block::push(int direction)
{
	_oldPos = getPosition();
	_newPos = _oldPos;
	if(direction%2 == 0)
		_newPos.x += 1-direction;
	else
		_newPos.z += direction-2;
	_moveTime = TOTAL_MOVE_TIME;
}

bool GO_Block::pushable()
{
	return _moveTime == 0;
}

int GO_Block::update_function(unsigned int time)
{
	if(!pushable())
	{
		_moveTime--;
		setPosition(interpolate(_newPos, _oldPos, _moveTime/TOTAL_MOVE_TIME));
	}
	Body::update_function(time);
	return 0;
}