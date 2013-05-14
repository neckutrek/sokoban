//
//  FPSCamera.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-16.
//
// hej

#include "DebugCamera.h"

DebugCamera::DebugCamera(GLfloat x, GLfloat y, GLfloat z) : Camera(x, y, z), _theta(M_PI/2), _phi(M_PI)
{}

void DebugCamera::setRelPosition(GLfloat dx, GLfloat dy, GLfloat dz)
{	
	vec3 forward = getViewDirection();
	vec3 right = CrossProduct(forward, getUpDirection());
	vec3 up = CrossProduct(right, forward);
	forward *= dz;
	right *= dx;
	up *= dy;
	
	vec3 dv = vec3(up.x - forward.x + right.x, up.y - forward.y + right.y, up.z - forward.z + right.z);
	
	setPosition(getPosition() + dv);
}

void DebugCamera::setViewDirection(GLfloat theta, GLfloat phi)
{
	_theta = clamp(theta, 0, M_PI);
	phi = fmod(phi,2*M_PI);
	if (phi < 0)
		phi += 2*M_PI;
	_phi = phi;
	Camera::setViewDirection(-sin(_theta)*sin(_phi), cos(_theta), sin(_theta)*cos(_phi));
}

void DebugCamera::setRelViewDirection(GLfloat dtheta, GLfloat dphi)
{
	setViewDirection(_theta + dtheta, _phi + dphi);
}

int DebugCamera::update_function(unsigned int time)
{
	std::cout << getPosition() << std::endl;
	
    InputManager& im = InputManager::getInstance();
    
    if (im.isKeyDown('w')) setRelPosition(0, 0, -0.1);
    else if (im.isKeyDown('s')) setRelPosition(0, 0, 0.1);
    
    if (im.isKeyDown('a')) setRelPosition(-0.1, 0, 0);
    else if (im.isKeyDown('d')) setRelPosition(0.1, 0, 0);
    
    if (im.isKeyDown(' ')) setRelPosition(0, 0.1, 0);
    else if (im.isKeyDown('<')) setRelPosition(0, -0.1, 0);
	
    setRelViewDirection(0.008 * im.getMouseSpeedY(),
                        0.008 * im.getMouseSpeedX());
        
    return 0;
}