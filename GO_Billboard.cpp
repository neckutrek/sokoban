//
//  Billboard.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-05-01.
//
//

#include "GO_Billboard.h"

GO_Billboard::GO_Billboard(vec3 pos, std::string texture) : GameObject(BoundingBox(0))
{
	loadModel("billboard.obj");
	addMaterial(texture.c_str(), 1, 1);
	setPosition(pos);
	_is_affected_by_light = false;
}

std::string GO_Billboard::getType()
{
	return "billboard";
}

int GO_Billboard::update_function(unsigned int time)
{
	vec3 newNormal = (-1)*(CameraManager::getInstance().getActiveCamera()->getViewDirection());
	vec3 xzDirVec = Normalize(vec3(newNormal.x, 0, newNormal.z));
	vec3 rotVec = CrossProduct(vec3(0,0,1), xzDirVec);
	if(Norm(rotVec)>0)
		setRot(rotVec.x, rotVec.y, rotVec.z, acos(vec3(0,0,1)*xzDirVec));
	Body::update_function(time);
	return 0;
}

int GO_Billboard::render(GLuint program_reference_id)
{
    glDepthMask(GL_FALSE);
	RenderableMultilayer::render(program_reference_id);
    glDepthMask(GL_TRUE);
}