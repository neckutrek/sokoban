#include "OpenGLCamera.h"

/* PRIVATE */
const CAMERA_MODE_FIXED = 1;
const CAMERA_MODE_FLEXIBLE = 2;

void priv_modAngles(GLfloat* theta, GLfloat* phi) {
	if (*theta < 0) *theta = 0;
	if (*theta > M_PI) *theta = M_PI;
	while (*phi < 0) *phi += 2*M_PI;
	while (*phi >= 2*M_PI) *phi -= 2*M_PI;
}

void priv_updateCameraDirection(OpenGLCamera* c, GLfloat theta, GLfloat phi) {
	c->viewDirection[0] = -sin(theta)*sin(phi);
	c->viewDirection[1] = cos(theta);
	c->viewDirection[2] = sin(theta)*cos(phi);	
}

/* PUBLIC */
void createOpenGLCamera(OpenGLCamera* c) {
	for (int i=0; i<3; i++) c->position[i] = 0;
	c->mode = CAMERA_MODE_FIXED;
	IdentityMatrix(c->cameraMatrix);

	c->upDirection[0] = 0;
	c->upDirection[1] = 1;
	c->upDirection[2] = 0;

	c->viewDirection[0] = 0;
	c->viewDirection[1] = 0;
	c->viewDirection[2] = -1;

	c->viewLocation[0] = 0;
	c->viewLocation[1] = 0;
	c->viewLocation[2] = -1;
	
	c->theta = M_PI;
	c->phi = 0;
}

void setCameraPosition(OpenGLCamera* c, GLfloat x, GLfloat y, GLfloat z) {
	c->position[0] = x;
	c->position[1] = y;
	c->position[2] = z;
}


void setCameraPositionX(OpenGLCamera* c, GLfloat arg) {c->position[0] = arg;}
void setCameraPositionY(OpenGLCamera* c, GLfloat arg) {c->position[1] = arg;}
void setCameraPositionZ(OpenGLCamera* c, GLfloat arg) {c->position[2] = arg;}

void setCameraRelPosition(OpenGLCamera* c, GLfloat dx, GLfloat dy, GLfloat dz) {
	c->position[0] += dx;
	c->position[1] += dy;
	c->position[2] += dz;
}

void moveCamera(OpenGLCamera* c, GLfloat dx, GLfloat dy, GLfloat dz) {
	Point3D forward = {c->viewDirection[0], c->viewDirection[1], c->viewDirection[2]};
	Point3D up = {c->upDirection[0], c->upDirection[1], c->upDirection[2]};
	Point3D right;

	CrossProduct(&forward, &up, &right);
	CrossProduct(&right, &forward, &up);

	c->position[0] += dy*up.x - dz*forward.x + dx*right.x;
	c->position[1] += dy*up.y - dz*forward.y + dx*right.y;
	c->position[2] += dy*up.z - dz*forward.z + dx*right.z;
}

void setCameraViewLocation(OpenGLCamera* c, GLfloat x, GLfloat y, GLfloat z) {
	c->viewLocation[0] = x;
	c->viewLocation[1] = y;
	c->viewLocation[2] = z;
	c->mode = CAMERA_MODE_FLEXIBLE;
}

void setCameraDirection3(OpenGLCamera* c, GLfloat x, GLfloat y, GLfloat z) {
	// For moving the camera along the viewDirection vector, this should be normalized
	GLfloat normFactor = 1/sqrt(x*x+y*y+z*z);
	c->viewDirection[0] = x*normFactor;
	c->viewDirection[1] = y*normFactor;
	c->viewDirection[2] = z*normFactor;
	c->mode = CAMERA_MODE_FIXED;
}

void setCameraDirection2(OpenGLCamera* c, GLfloat theta, GLfloat phi) {
	c->theta = theta;
	c->phi = phi;
	c->mode = CAMERA_MODE_FIXED;
	priv_modAngles(&c->theta, &c->phi);
	priv_updateCameraDirection(c, c->theta, c->phi);
}

void setCameraRelDirection2(OpenGLCamera* c, GLfloat dtheta, GLfloat dphi) {
	c->theta += dtheta;
	c->phi += dphi;
	c->mode = CAMERA_MODE_FIXED;
	priv_modAngles(&c->theta, &c->phi);
	priv_updateCameraDirection(c, c->theta, c->phi);
}

void updateCamera(OpenGLCamera* c) {
	if (c->mode == CAMERA_MODE_FIXED)
		for (int i=0; i<3; i++)
			c->viewLocation[i] = c->position[i] + c->viewDirection[i];

	Point3D p = {c->position[0], c->position[1], c->position[2]};
	Point3D l = {c->viewLocation[0], c->viewLocation[1], c->viewLocation[2]};
	lookAt(&p, &l, c->upDirection[0], c->upDirection[1], c->upDirection[2], c->cameraMatrix);
}
