//
//  Block.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-05-01.
//
//

#ifndef __OpenGLGLUTApp__Block__
#define __OpenGLGLUTApp__Block__

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "GameObjectManager.h"
#include "GO_Button.h"


class GO_Block : public GameObject
{
public:
	GO_Block(vec3 pos);
	~GO_Block() {}
	std::string getType();
	
	//0=right, 1=up, 2=left, 3=down
	void push(int direction);
	bool pushable();
	
	virtual int update_function(unsigned int time);
	
protected:
	
private:
	static const int TOTAL_MOVE_TIME = 10;
	int _moveTime = 0;
	vec3 _oldPos, _newPos;
	
};

#endif /* defined(__OpenGLGLUTApp__Block__) */
