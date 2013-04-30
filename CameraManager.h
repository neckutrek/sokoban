//
//  CameraManager.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-18.
//
// hej

#ifndef __OpenGLGLUTApp__CameraManager__
#define __OpenGLGLUTApp__CameraManager__

#include <iostream>
#include "CutsceneCamera.h"

//Innehåller frustuminställningar, aktiv kamera och kör kamerauppdateringar som inte har någon annan logisk plats. Kamerakod lyft ur maindelen typ.

class CameraManager
{
public:
	static CameraManager& getInstance()
	{
		static CameraManager instance;
		return instance;
	}
	
	void setActiveCamera(Camera* c);
	Camera* getActiveCamera();
	void update(int dtime);
	
protected:
	
private:
	Camera* _activeCamera;
	Camera* _previousCamera;
	CameraManager();
	CameraManager(const CameraManager&);
	CameraManager& operator=(const CameraManager&);
	
};

#endif /* defined(__OpenGLGLUTApp__CameraManager__) */
