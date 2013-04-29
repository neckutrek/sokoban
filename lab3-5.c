// Lab 1-1.
// This is the same as the first simple example in the course book,
// but with a few error checks.
// Remember to copy your file to a new on appropriate places during the lab so you keep old results.
// Note that the files "lab1-1.frag", "lab1-1.vert" are required.

// Includes vary a bit with platforms.
// MS Windows needs GLEW or glee.
// Mac uses slightly different paths.

#include "GL_utilities.h"
#include "VectorUtils2.h"
#include "loadobj.h"
#include "LoadTGA.h"
#include "OpenGLObject.h"
#include "OpenGLCamera.h"
#include <math.h>
#include <time.h>

#define near 1.0
#define far 1000.0
#define right 1.2
#define left -1.2
#define top 1.2
#define bottom -1.2

typedef struct {
	GLfloat rotationSpeed;
	Model* model;
	GLfloat matrix[16];
	GLuint texture;
} GameObject;

const GLint WINDOW_WIDTH = 1024;
const GLint WINDOW_HEIGHT = 1024;
const GLfloat MOUSE_SENSITIVITY = 1.0f/200.0f;
const GLint fps = 30;
GLuint program;
GLfloat projectionMatrix[] = {2.0f*near/(right-left), 0.0f, (right+left)/(right-left), 0.0f,
                              0.0f, 2.0f*near/(top-bottom), (top+bottom)/(top-bottom), 0.0f,
                              0.0f, 0.0f, -(far + near)/(far - near), -2*far*near/(far - near),
                              0.0f, 0.0f, -1.0f, 0.0f };
OpenGLObject objects[3];
OpenGLObject blades[4];
OpenGLObject staticObjects[4];
OpenGLObject theCows[100];
OpenGLObject skybox;

OpenGLCamera camera;
int keyboardMap[256];

void OnTimer(int value);
void updateObjects(GLfloat time);
void setKeyUp(unsigned char key, int x, int y);
void setKeyDown(unsigned char key, int x, int y);
void updateKeyboard();
void updateMouse(int x, int y);
void initTextureUnits();

void init(void)
{
	dumpInfo();
	glClearColor(0.4, 0.4, 0.8, 0);
	glEnable(GL_DEPTH_TEST);
	program = loadShaders("lab3-5.vert", "lab3-5.frag");
	initTextureUnits();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLuint tex;
	Model* m;


	Point3D lightSourcesColorsArr[] = { {1.0f, 0.0f, 0.0f}, // Red light
		                             {0.0f, 1.0f, 0.0f}, // Green light
		                             {0.0f, 0.0f, 1.0f}, // Blue light
		                             {1.0f, 1.0f, 1.0f} }; // White light

	GLfloat specularExponent[] = {20.0, 20.0, 60.0, 5.0};
	GLint isDirectional[] = {1,1,1,1};

	Point3D lightSourcesDirectionsPositions[] = { {10.0f, 5.0f, 0.0f}, // Red light, positional
		                                   {0.0f, 5.0f, 10.0f}, // Green light, positional
		                                   {-1.0f, 0.0f, 0.0f}, // Blue light along X
		                                   {-10.0f, 5.0f, 0.0f} }; // White light along Z

	glUniform3fv(glGetUniformLocation(program, "lightSourcesDirPosArr"), 4, &lightSourcesDirectionsPositions[0].x);
	glUniform3fv(glGetUniformLocation(program, "lightSourcesColorArr"), 4, &lightSourcesColorsArr[0].x);
	glUniform1fv(glGetUniformLocation(program, "specularExponent"), 4, specularExponent);
	glUniform1iv(glGetUniformLocation(program, "isDirectional"), 4, isDirectional);


	m = LoadModelPlus("skybox.obj", program, "inPosition", "inNormal", "inTexCoord");
	LoadTGATextureSimple("SkyBox512.tga", &tex);
	skybox = createOpenGLObject(m);
	addTextureToObject(&skybox, tex);
	setObjectPosition(&skybox, 0, 0, 0);
	setObjectScaling(&skybox, 100, 100, 100);

	m = LoadModelPlus("models/windmill/windmill-walls.obj", program, "inPosition", "inNormal", "inTexCoord");
	LoadTGATextureSimple("conc.tga", &tex);
	objects[0] = createOpenGLObject(m);
	addTextureToObject(&objects[0], tex);

	m = LoadModelPlus("models/windmill/windmill-roof.obj", program, "inPosition", "inNormal", "inTexCoord");
	LoadTGATextureSimple("grass.tga", &tex);
	objects[1] = createOpenGLObject(m);
	addTextureToObject(&objects[1], tex);

	m = LoadModelPlus("models/windmill/windmill-balcony.obj", program, "inPosition", "inNormal", "inTexCoord");
	LoadTGATextureSimple("grass.tga", &tex);
	objects[2] = createOpenGLObject(m);
	addTextureToObject(&objects[2], tex);

	for (int i=0; i<sizeof(objects)/sizeof(objects[0]); i++) {
		setObjectRotation(&objects[i], 0, 1, 0, -2*M_PI/4);
	}

	m = LoadModelPlus("models/windmill/blade.obj", program, "inPosition", "inNormal", "inTexCoord");
	LoadTGATextureSimple("SkyBox512.tga", &tex);
	for (int i=0; i<sizeof(blades)/sizeof(blades[0]); i++) {
		blades[i] = createOpenGLObject(m);
		addTextureToObject(&blades[i], tex);
		setObjectPosition(&blades[i], 0, 9.2, 5);
		setObjectRotation(&blades[i], 0, 0, 1, 2*M_PI/4*i);
		setObjectRotationVel(&blades[i], 0, 0, 1, 0.02);
	}

	m = LoadModelPlus("models/various/ground.obj", program, "inPosition", "inNormal", "inTexCoord");
	LoadTGATextureSimple("grass.tga", &tex);
	staticObjects[0] = createOpenGLObject(m);
	addTextureToObject(&staticObjects[0], tex);

	m = LoadModelPlus("models/castle/walls.obj", program, "inPosition", "inNormal", "inTexCoord");
	LoadTGATextureSimple("conc.tga", &tex);
	staticObjects[1] = createOpenGLObject(m);
	addTextureToObject(&staticObjects[1], tex);
	setObjectPosition(&staticObjects[1], 200, 0, -50);

	m = LoadModelPlus("models/castle/rooftops.obj", program, "inPosition", "inNormal", "inTexCoord");
	LoadTGATextureSimple("grass.tga", &tex);
	staticObjects[2] = createOpenGLObject(m);
	addTextureToObject(&staticObjects[2], tex);
	setObjectPosition(&staticObjects[2], 200, 0, -50);

	m = LoadModelPlus("bunnyplus.obj", program, "inPosition", "inNormal", "inTexCoord");
	LoadTGATextureSimple("grass.tga", &tex);
	staticObjects[3] = createOpenGLObject(m);
	addTextureToObject(&staticObjects[3], tex);
	LoadTGATextureSimple("SkyBox512.tga", &tex);
	addTextureToObject(&staticObjects[3], tex);
	setObjectPosition(&staticObjects[3], -100, 30, 10);
	setObjectScaling(&staticObjects[3], 50, 50, 50);

	m = LoadModelPlus("models/various/cow.obj", program, "inPosition", "inNormal", "inTexCoord");
	LoadTGATextureSimple("grass.tga", &tex);
	for (int i=0; i<sizeof(theCows)/sizeof(theCows[0]); i++) {
		theCows[i] = createOpenGLObject(m);
		addTextureToObject(&theCows[i], tex);
		setObjectPosition(&theCows[i], rand()%1000-500, 1, rand()%1000-500);	
		setObjectRotation(&theCows[i], 0, 1, 0, (rand()%31415)/5000.0f);
	}

	createOpenGLCamera(&camera);
	setCameraPosition(&camera, 0, 10, 10);
	setCameraDirection3(&camera, 0, 0, -1);

	for (int i=0; i<256; i++)
		keyboardMap[i] = 0;

	glutTimerFunc(1000/fps, &OnTimer, 0);
	printError("init arrays");
}

void initTextureUnits() {
	GLint texUnits[48];
	for (int i=0; i<48; i++) {
		texUnits[i] = i;
	}
	glUniform1iv(glGetUniformLocation(program, "tex"), 48, &texUnits[0]);
}

void display(void)
{
	printError("pre display");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glUniformMatrix4fv(glGetUniformLocation(program, "wtcMatrix"), 1, GL_TRUE, camera.cameraMatrix);
	glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, GL_TRUE, projectionMatrix);

	glDisable(GL_DEPTH_TEST);
	drawObject(&skybox, program);
	glEnable(GL_DEPTH_TEST);

	for(int i=0; i<sizeof(objects)/sizeof(objects[0]); i++) drawObject(&objects[i], program);
	for(int i=0; i<sizeof(blades)/sizeof(blades[0]); i++) drawObject(&blades[i], program);
	for(int i=0; i<sizeof(staticObjects)/sizeof(staticObjects[0]); i++) drawObject(&staticObjects[i], program);
	for(int i=0; i<sizeof(theCows)/sizeof(theCows[0]); i++) drawObject(&theCows[i], program);

	glutSwapBuffers();
	printError("display");
}

void OnTimer(int value)
{
    GLfloat t = (GLfloat)glutGet(GLUT_ELAPSED_TIME);
	updateObjects(t);
	updateCamera(&camera);
	updateKeyboard();
    glutPostRedisplay();
    glutTimerFunc(1000/fps, &OnTimer, value);
}

void updateObjects(GLfloat time) {
	for(int i=0; i<sizeof(objects)/sizeof(objects[0]); i++) updateObject(&objects[i], time);
	for(int i=0; i<sizeof(blades)/sizeof(blades[0]); i++) updateObject(&blades[i], time);
	for(int i=0; i<sizeof(staticObjects)/sizeof(staticObjects[0]); i++) updateObject(&staticObjects[i], time);
	for(int i=0; i<sizeof(theCows)/sizeof(theCows[0]); i++) updateObject(&theCows[i], time);
	setObjectPosition(&skybox, camera.position[0], 0.0, camera.position[2]); 
	updateObject(&skybox, time);
}

void setKeyUp(unsigned char key, int x, int y) {
	keyboardMap[key] = 0;
}

void setKeyDown(unsigned char key, int x, int y) {
	keyboardMap[key] = 1;
}

void updateKeyboard() {
	if (keyboardMap['W'] == 1 || keyboardMap['w'] == 1) {
		moveCamera(&camera, 0, 0, -1.0);
	} else if (keyboardMap['S'] == 1 || keyboardMap['s'] == 1) {
		moveCamera(&camera, 0, 0, 1.0);
	} 

	if (keyboardMap['A'] == 1 || keyboardMap['a'] == 1) {
		moveCamera(&camera, -1.0, 0, 0);
	} else if (keyboardMap['D'] == 1 || keyboardMap['d'] == 1) {
		moveCamera(&camera, 1.0, 0, 0);
	}

	if (keyboardMap[32] == 1) {
		moveCamera(&camera, 0, 1.0, 0);
	} else if (keyboardMap['>'] == 1 || keyboardMap['<'] == 1) {
		moveCamera(&camera, 0, -1.0, 0);
	}
}

void updateMouse(int x, int y) {
	GLfloat dx = x - WINDOW_WIDTH/2;
	GLfloat dy = y - WINDOW_HEIGHT/2;
	//glutWarpPointer(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	setCameraDirection2(&camera, y*MOUSE_SENSITIVITY, x*MOUSE_SENSITIVITY);
}

int main(int argc, char** argv)
{
	srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow ("GL3 white triangle example");
	glutDisplayFunc(display);
	glutPassiveMotionFunc(updateMouse);
	glutKeyboardFunc(setKeyDown);
	glutKeyboardUpFunc(setKeyUp);
	init();
	glutMainLoop();
}
