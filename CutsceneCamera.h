//
//  CutsceneCamera.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-18.
//
// hej

#ifndef __OpenGLGLUTApp__CutsceneCamera__
#define __OpenGLGLUTApp__CutsceneCamera__

#include <iostream>
#include "Camera.h"
#include <vector>

struct CameraWaypoint
{
	vec3 pos;
	vec3 dir;
	int time;
};

class CutsceneCamera : public Camera
{
public:
	CutsceneCamera(GLfloat x=0, GLfloat y=0, GLfloat z=0);
	
	~CutsceneCamera() {}
	
	void addWaypoint(CameraWaypoint waypoint);
	void addWaypoint(vec3 pos, vec3 dir, GLfloat time);
	void clearTrack() {_waypoints.clear();}
	
	bool trackFinished();
	void reset() {_time = 0;}
	
    virtual int update_function(unsigned int time);
	
protected:
	
private:
	std::vector<CameraWaypoint> _waypoints;
	GLfloat _time;
};

#endif /* defined(__OpenGLGLUTApp__CutsceneCamera__) */
