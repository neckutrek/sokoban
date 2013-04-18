//
//  CutsceneCamera.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-18.
//
//

#ifndef __OpenGLGLUTApp__CutsceneCamera__
#define __OpenGLGLUTApp__CutsceneCamera__

#include <iostream>
#include "Camera.h"

class CutsceneCamera : public Camera
{
public:
	CutsceneCamera(GLfloat x=0, GLfloat y=0, GLfloat z=0);
	
	~CutsceneCamera() {}
	
	void setStartPos(vec3 startPos);
	void setEndPos(vec3 endPos);
	void setStartViewLoc(vec3 startViewLoc);
	void setEndViewLoc(vec3 endViewLoc);
	void setTime(GLfloat time);
	bool isDone() {return _currTime > _time;}
	void reset() {_currTime = 0;}
	
    virtual int update_function(unsigned int time);
	
protected:
	vec3 interpolate(vec3 v1, vec3 v2);
	
private:
	vec3 _startPos;
	vec3 _endPos;
	vec3 _startViewLoc;
	vec3 _endViewLoc;
	GLfloat _time;
	GLfloat _currTime;
};

#endif /* defined(__OpenGLGLUTApp__CutsceneCamera__) */
