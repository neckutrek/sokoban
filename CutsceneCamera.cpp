//
//  CutsceneCamera.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-18.
//
//

#include "CutsceneCamera.h"

CutsceneCamera::CutsceneCamera(GLfloat x, GLfloat y, GLfloat z) : Camera(x, y, z)
{}

void CutsceneCamera::addWaypoint(CameraWaypoint waypoint)
{
	int insertIndex = _waypoints.size();
	for(int i=0; i<_waypoints.size(); i++)
	{
		if(_waypoints[i].time > waypoint.time)
		{
			insertIndex = i;
			break;
		}
	}
	_waypoints.insert(_waypoints.begin()+insertIndex, waypoint);
}

void CutsceneCamera::addWaypoint(vec3 pos, vec3 dir, GLfloat time)
{
	CameraWaypoint c = {pos, dir, time};
	addWaypoint(c);
}

bool CutsceneCamera::trackFinished()
{
	return _waypoints.size() == 0 || _time >= _waypoints.back().time;
}

int CutsceneCamera::update_function(unsigned int time)
{
	_time++;
	if(trackFinished())
		return 0;
	if(_waypoints.size() == 1 || _time < _waypoints.front().time)
	{
		setPosition(_waypoints.front().pos);
		setViewLocation(_waypoints.front().dir);
	}
	else
	{
		int firstWaypointIndex;
		for(int i=0; i<_waypoints.size(); i++)
		{
			if(_time < _waypoints[i].time)
			{
				firstWaypointIndex = (i==0 ? 0 : i-1);
				break;
			}
		}
		
		CameraWaypoint* waypoint1 = &_waypoints[firstWaypointIndex];
		CameraWaypoint* waypoint2 = &_waypoints[firstWaypointIndex+1];
		GLfloat factor = (_time - waypoint1->time)/(waypoint2->time - waypoint1->time);
		
		setPosition(interpolate(waypoint1->pos, waypoint2->pos, factor));
		setViewLocation(interpolate(waypoint1->dir, waypoint2->dir, factor));
	}
	return 0;
}