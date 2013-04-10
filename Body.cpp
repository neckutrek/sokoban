//
//  Body.cpp
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/4/13.
//
//

#include "Body.h"

void Body::setRot(GLfloat x, GLfloaty, GLfloat z, GLfloat a)
{
	rotMatrix = ArbRotate(vec3(x, y, z), a);
}

void Body::setRotVelocity(GLfloat dx, GLfloat dy, GLfloat dz, GLfloat da)
{
	rotVelMatrix = ArbRotate(vec3(x, y, z), a);
}

void Body::setRotAcceleration(GLfloat dx, GLfloat dy, GLfloat dz, GLfloat da)
{
	rotAccMatrix = ArbRotate(vec3(x, y, z), a);
}

//This update function should be called first in inheriting classes, to ensure the correct multiplication order.
int Body::update_function(unsigned int time)
{
	Particle::update_function(time);
	//Update velocity
	
	return 0;
}