/*
	OpenGLCamera c-class

		Place the camera at a position in the world (x,y,z)
		Indirect: Set camera mode (FIXED, FLEXIBLE)
		Direct the camera towards a point (x,y,z) (sets mode FLEXIBLE)
		Direct camera in a shperical direction (theta, phi) (sets mode FIXED)
		Direct camera in a chartesian direction (x, y, z) (sets mode FIXED)
*/

#include <math.h>
#include "VectorUtils3.h"

#ifndef __OPENGLCAMERA_H__
#define __OPENGLCAMERA_H__

typedef struct {
	GLfloat position[3];
	GLint mode;
	GLfloat cameraMatrix[16];
	GLfloat upDirection[3];

	GLfloat viewDirection[3];
	GLfloat viewLocation[3];
	GLfloat theta;
	GLfloat phi;
} OpenGLCamera;

void createOpenGLCamera(OpenGLCamera* c);

void setCameraPosition(OpenGLCamera* c, GLfloat x, GLfloat y, GLfloat z);
void setCameraPositionX(OpenGLCamera* c, GLfloat arg);
void setCameraPositionY(OpenGLCamera* c, GLfloat arg);
void setCameraPositionZ(OpenGLCamera* c, GLfloat arg);
void setCameraRelPosition(OpenGLCamera* c, GLfloat dx, GLfloat dy, GLfloat dz);

//Moves a camera relative to the cameras viewing direction
void moveCamera(OpenGLCamera* c, GLfloat dx, GLfloat dy, GLfloat dz);

//void setCameraModeFixed(OpenGLCamera* c);
//void setCameraModeFlexible(OpenGLCamera* c);

void setCameraViewLocation(OpenGLCamera* c, GLfloat x, GLfloat y, GLfloat z);

void setCameraDirection3(OpenGLCamera* c, GLfloat x, GLfloat y, GLfloat z);
void setCameraDirection2(OpenGLCamera* c, GLfloat theta, GLfloat phi);
void setCameraRelDirection2(OpenGLCamera* c, GLfloat dtheta, GLfloat dphi);

void updateCamera(OpenGLCamera* c);

#endif
