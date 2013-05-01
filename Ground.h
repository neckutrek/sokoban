//
//  Ground.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-30.
//
//

#ifndef __OpenGLGLUTApp__Ground__
#define __OpenGLGLUTApp__Ground__

#include <iostream>
#include "GameObject.h"
#include "CameraManager.h"

class Ground : public GameObject
{
public:
	Ground();
	~Ground() {}
	std::string getType();
	
protected:
	
private:
	
};

#endif /* defined(__OpenGLGLUTApp__Ground__) */
