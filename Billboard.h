//
//  Billboard.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-05-01.
//
//

#ifndef __OpenGLGLUTApp__Billboard__
#define __OpenGLGLUTApp__Billboard__

#include <iostream>
#include "GameObject.h"
#include "CameraManager.h"

class Billboard : public GameObject
{
public:
	Billboard(vec3 pos);
	~Billboard() {}
	std::string getType();
	
	virtual int update_function(unsigned int time);
	
protected:
	
private:
	
};

#endif /* defined(__OpenGLGLUTApp__Billboard__) */
