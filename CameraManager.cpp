//
//  CameraManager.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-18.
//
//

#include "CameraManager.h"

void CameraManager::setActiveCamera(Camera* c)
{
	if(dynamic_cast<CutsceneCamera*>(c) != NULL)
		_previousCamera = _activeCamera;
	_activeCamera = c;
}

Camera* CameraManager::getActiveCamera()
{
	return _activeCamera;
}

CameraManager::CameraManager() : _activeCamera(new Camera(0, 0, 5))
{}

void CameraManager::update()
{
	CutsceneCamera* cc = dynamic_cast<CutsceneCamera*>(_activeCamera);
	if(cc != NULL && cc->trackFinished())
	{
		cc->reset();
		_activeCamera = _previousCamera;
	}
}