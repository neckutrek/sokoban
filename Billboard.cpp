//
//  Billboard.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-05-01.
//
//

#include "Billboard.h"

Billboard::Billboard(vec3 pos) : GameObject(BoundingBox(0))
{
	loadModel("billboard.obj");
	setPosition(pos);
}

std::string Billboard::getType()
{
	return "billboard";
}

int Billboard::update_function(unsigned int time)
{
	vec3 camVec = Normalize(CameraManager::getInstance().getActiveCamera()->getPosition() - getPosition());
	mat4 rotMat = getRot();
	vec3 dirVec = vec3(rotMat.m[2], rotMat.m[6], rotMat.m[10]); //Normalize?
	vec3 rotVec = CrossProduct(camVec, dirVec);
	setRot(rotVec.x, rotVec.y, rotVec.z, acos(camVec*dirVec));
	std::cout << camVec << std::endl << dirVec << std::endl << acos(camVec*dirVec) << std::endl;
	Body::update_function(time);
	return 0;
}