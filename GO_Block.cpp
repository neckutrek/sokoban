//
//  Block.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-05-01.
//
//

#include "GO_Block.h"
#include "SigmaGameEngine.h"

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
	vec3 potentialNewPos = getPosition();
	if(direction%2 == 0)
		potentialNewPos.x += 1-direction;
	else
		potentialNewPos.z += direction-2;
	if(GameObjectManager::getInstance().check_boundingbox_collision(BoundingBox(0) + potentialNewPos))
	   return;
	_oldPos = getPosition();
	_newPos = potentialNewPos;
	_moveTime = TOTAL_MOVE_TIME;
	
	GO_Button* b;
	std::vector<GameObject*> buttons = GameObjectManager::getInstance().getObjectsFromType("button");
	for(std::vector<GameObject*>::iterator it=buttons.begin(); it != buttons.end(); ++it)
	{
		b = dynamic_cast<GO_Button*>(*it);
		if(Norm(getPosition() - vec3(0,0.5,0) - b->getPosition()) < 0.001)
		{
			b->setPressed(false);
		}
	}
	setScaling(1, 1, 1);
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
		setPosition(interpolate(_newPos, _oldPos, (GLfloat)_moveTime/(GLfloat)TOTAL_MOVE_TIME));
		
		if(_moveTime==0)
		{
			GO_Button* b;
			std::vector<GameObject*> buttons = GameObjectManager::getInstance().getObjectsFromType("button");
			for(std::vector<GameObject*>::iterator it=buttons.begin(); it != buttons.end(); ++it)
			{
				b = dynamic_cast<GO_Button*>(*it);
				if(Norm(getPosition() - vec3(0,0.5,0) - b->getPosition()) < 0.001)
				{
					setScaling(0.8, 0.8, 0.8);
					b->setPressed(true);
					SigmaGameEngine::getInstance().winCheck();
				}
			}
		}
	}
	Body::update_function(time);
	return 0;
}