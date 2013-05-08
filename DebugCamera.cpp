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

void DebugCamera::updateKeyboard(unsigned char keyboardMap[256])
{
	if (keyboardMap['W'] == 1 || keyboardMap['w'] == 1) {
		setRelPosition(0, 0, -0.1);
	} else if (keyboardMap['S'] == 1 || keyboardMap['s'] == 1) {
		setRelPosition(0, 0, 0.1);
	}
	
	if (keyboardMap['A'] == 1 || keyboardMap['a'] == 1) {
		setRelPosition(-0.1, 0, 0);
	} else if (keyboardMap['D'] == 1 || keyboardMap['d'] == 1) {
		setRelPosition(0.1, 0, 0);
	}
	
	if (keyboardMap['I'] == 1 || keyboardMap['i'] == 1) {
		setRelViewDirection(-0.05, 0);
	} else if (keyboardMap['K'] == 1 || keyboardMap['k'] == 1) {
		setRelViewDirection(0.05, 0);
	}
	
	if (keyboardMap['J'] == 1 || keyboardMap['j'] == 1) {
		setRelViewDirection(0, -0.05);
	} else if (keyboardMap['L'] == 1 || keyboardMap['l'] == 1) {
		setRelViewDirection(0, 0.05);
	}
	 
	if (keyboardMap[32] == 1) {
		setRelPosition(0, 0.1, 0);
	} else if (keyboardMap['>'] == 1 || keyboardMap['<'] == 1) {
		setRelPosition(0, -0.1, 0);
	}
}