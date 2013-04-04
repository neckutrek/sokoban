#include "OpenGLObject.h"
#include <math.h>
#include <stdio.h>

OpenGLObject createOpenGLObject(Model* m) {
	OpenGLObject o;
	o.model = m;

	IdentityMatrix(o.transMatrix);
	IdentityMatrix(o.rotMatrix);
	IdentityMatrix(o.rotVelMatrix);
	IdentityMatrix(o.rotAccMatrix);
	IdentityMatrix(o.scaleMatrix);
	IdentityMatrix(o.resultMatrix);

	for (int i=0; i<3; i++) o.velVector[i] = o.accVector[i] = 0;

	o.nTextures = 0;
	return o;
}

void addTextureToObject(OpenGLObject* o, GLuint tex) {
	if (o->nTextures < sizeof(o->textures)/sizeof(o->textures[0])) {
		o->textures[o->nTextures] = tex;
		o->nTextures += 1;
	}
}

/* TRANSLATION */

void setObjectPosition(OpenGLObject* o, GLfloat x, GLfloat y, GLfloat z) {
	T(x, y, z, o->transMatrix);
}
 
void setObjectVel(OpenGLObject* o, GLfloat dx, GLfloat dy, GLfloat dz) {
	o->velVector[0] = dx;
	o->velVector[1] = dy;
	o->velVector[2] = dz;
}

void setObjectAcc(OpenGLObject* o, GLfloat ddx, GLfloat ddy, GLfloat ddz) {
	o->accVector[0] = ddx;
	o->accVector[1] = ddy;
	o->accVector[2] = ddz;
}

/* ROTATION */

void setObjectRotation(OpenGLObject* o, GLfloat x, GLfloat y, GLfloat z, GLfloat a) {
	Point3D p = {x, y, z};
	ArbRotate(&p, a, o->rotMatrix);
}

void setObjectRotationVel(OpenGLObject* o, GLfloat dx, GLfloat dy, GLfloat dz, GLfloat da) {
	Point3D p = {dx, dy, dz};
	ArbRotate(&p, da, o->rotVelMatrix);
}

void setObjectRotationAcc(OpenGLObject* o, GLfloat ddx, GLfloat ddy, GLfloat ddz, GLfloat dda) {
	Point3D p = {ddx, ddy, ddz};
	ArbRotate(&p, dda, o->rotAccMatrix);
}

/* SCALING */

void setObjectScaling(OpenGLObject* o, GLfloat x, GLfloat y, GLfloat z) {
	S(x, y, z, o->scaleMatrix);
}

/* UPDATE */

void updateObject(OpenGLObject* o, GLfloat time) {
	GLfloat norm;
	IdentityMatrix(o->resultMatrix);
	
	// Update velocity
	for (int i=0; i<3; i++)	o->velVector[i] += o->accVector[i];
	GLfloat velMatrix[16]; T(o->velVector[0], o->velVector[1], o->velVector[2], velMatrix);
	Mult(velMatrix, o->transMatrix, o->transMatrix);

	// Update rotation velocity
	Mult(o->rotAccMatrix, o->rotVelMatrix, o->rotVelMatrix);
	Mult(o->rotVelMatrix, o->rotMatrix, o->rotMatrix);

	//Update result matrix
	Mult(o->resultMatrix, o->transMatrix, o->resultMatrix);
	Mult(o->resultMatrix, o->rotMatrix, o->resultMatrix);
	Mult(o->resultMatrix, o->scaleMatrix, o->resultMatrix);
	
//	Mult(o->transMatrix, o->rotMatrix, o->resultMatrix);
	//Mult(o->resultMatrix, o->scaleMatrix, o->resultMatrix);
}

void drawObject(OpenGLObject* o, GLuint program) {
	glBindVertexArray(o->model->vao);
	glUniformMatrix4fv(glGetUniformLocation(program, "mtwMatrix"), 1, GL_TRUE, o->resultMatrix);
	glUniform1i(glGetUniformLocation(program, "nTextures"), o->nTextures);
	
	for (int i=0; i<o->nTextures; i++) {
		switch (i) {
			case 0: glActiveTexture(GL_TEXTURE0); break;
			case 1: glActiveTexture(GL_TEXTURE1); break;
			case 2: glActiveTexture(GL_TEXTURE2); break;
			case 3: glActiveTexture(GL_TEXTURE3); break;
			case 4: glActiveTexture(GL_TEXTURE4); break;
			case 5: glActiveTexture(GL_TEXTURE5); break;
			case 6: glActiveTexture(GL_TEXTURE6); break;
			case 7: glActiveTexture(GL_TEXTURE7); break;
			case 8: glActiveTexture(GL_TEXTURE8); break;
			case 9: glActiveTexture(GL_TEXTURE9); break;
		}
		glBindTexture(GL_TEXTURE_2D, o->textures[i]);
	}
	
	glDrawElements(GL_TRIANGLES, o->model->numIndices, GL_UNSIGNED_INT, 0L);
}

