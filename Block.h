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
#include "GameObject.h"

class Block : public GameObject
{
public:
	Block(vec3 pos);
	~Block() {}
	std::string getType();
	
protected:
	
private:
	
};

#endif /* defined(__OpenGLGLUTApp__Block__) */
