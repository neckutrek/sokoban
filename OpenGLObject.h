/*
	OpenGLObject c-class
*/

#include "GL_utilities.h"
#include "VectorUtils2.h"
#include "loadobj.h"
#include "LoadTGA2.h"

#ifndef __OPENGLOBJECT_H__
#define __OPENGLOBJECT_H__

typedef struct {
	Model* model;

	GLfloat transMatrix[4][4];
	GLfloat rotMatrix[4][4];
	GLfloat rotVelMatrix[4][4];
	GLfloat rotAccMatrix[4][4];
	GLfloat scaleMatrix[4][4];
	GLfloat resultMatrix[4][4];

	GLfloat velVector[3];
	GLfloat accVector[3];

	GLuint textures[10];
	int nTextures; // the number of currently used textures
} OpenGLObject;

OpenGLObject createOpenGLObject(Model* m);
void addTextureToObject(OpenGLObject* o, GLuint tex);

void setObjectPosition(OpenGLObject* o, GLfloat x, GLfloat y, GLfloat z);
void setObjectVel(OpenGLObject* o, GLfloat dx, GLfloat dy, GLfloat dz);
void setObjectAcc(OpenGLObject* o, GLfloat ddx, GLfloat ddy, GLfloat ddz);

void setObjectRotation(OpenGLObject* o, GLfloat x, GLfloat y, GLfloat z, GLfloat a);
void setObjectRotationVel(OpenGLObject* o, GLfloat dx, GLfloat dy, GLfloat dz, GLfloat da);
void setObjectRotationAcc(OpenGLObject* o, GLfloat ddx, GLfloat ddy, GLfloat ddz, GLfloat dda);

void setObjectScaling(OpenGLObject* o, GLfloat x, GLfloat y, GLfloat z);
void updateObject(OpenGLObject* o, GLfloat time);
void drawObject(OpenGLObject* o, GLuint program);



/*
void update_matrix(int t, GameObject* o) {
	GLfloat a = t/o->rotationSpeed * 2*3.141592f;
	GLfloat rot3d[16];
	GLfloat translate[16]; T(0.5*sin(0.4*a), 0.5*sin(0.5*a), 0.5*sin(0.6*a), translate);
	//GLfloat rx[16]; Rx(a, rx);
	GLfloat ry[16]; Ry(a, ry);
	//Mult(translate, rx, rx);
	Mult(translate, ry, rot3d);

	for (int i=0; i<16; i++) o->matrix[i] = rot3d[i];
}
*/

#endif
