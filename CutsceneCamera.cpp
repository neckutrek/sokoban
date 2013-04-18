//
//  CutsceneCamera.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-18.
//
//

#include "CutsceneCamera.h"

CutsceneCamera::CutsceneCamera(GLfloat x, GLfloat y, GLfloat z) : Camera(x, y, z),
_startPos(vec3(0,0,0)), _endPos(vec3(0,0,0)), _startViewLoc(vec3(0,0,0)), _endViewLoc(vec3(0,0,0)), _time(3), _currTime(0)
{}

void CutsceneCamera::setStartPos(vec3 startPos)
{
	_startPos = startPos;
}

void CutsceneCamera::setEndPos(vec3 endPos)
{
	_endPos = endPos;
}

void CutsceneCamera::setStartViewLoc(vec3 startViewLoc)
{
	_startViewLoc = startViewLoc;
}

void CutsceneCamera::setEndViewLoc(vec3 endViewLoc)
{
	_endViewLoc = endViewLoc;
}

void CutsceneCamera::setTime(GLfloat time)
{
	_time = time;
}

vec3 CutsceneCamera::interpolate(vec3 v1, vec3 v2)
{
	GLfloat factor = 1/(1+exp((0.5-_currTime/_time)*10));
	return (1-factor)*v1 + factor*v2;
}

int CutsceneCamera::update_function(unsigned int time)
{
	//_currTime+=((GLfloat)time)/1000;
	_currTime++;
	std::cout << time << std::endl;
	setPosition(interpolate(_startPos, _endPos));
	setViewLocation(interpolate(_startViewLoc, _endViewLoc));
	return 0;
}