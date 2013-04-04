//
//  Body.h
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/4/13.
//
//

#ifndef __OpenGLGLUTApp__Body__
#define __OpenGLGLUTApp__Body__

#include "Particle.h"

class Body : public Particle {
public:
	//Constructor
	//Destructor
	
	void setRot();
	void setRotVelocity();
	void setRotAcceleration();
	
	vec3 getRot();
	vec3 getRotVelocity();
	vec3 getRotAcceleration();
	
	int update_function(unsigned int time);
	
protected:
	
private:
    vec3 _rot;
    vec3 _rot_velocity;
    vec3 _rot_acceleration;
	
};

#endif /* defined(__OpenGLGLUTApp__Body__) */
