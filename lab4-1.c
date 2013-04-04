// Lab 4, terrain generation

#ifdef __APPLE__
	#include <OpenGL/gl3.h>
	#include "MicroGlut.h"
	// Linking hint for Lightweight IDE
	// uses framework Cocoa
#endif
#include "GL_utilities.h"
#include "VectorUtils2.h"
#include "OpenGLObject.h"
#include "OpenGLCamera.h"
#include "loadobj.h"
#include "LoadTGA2.h"
#include <stdlib.h>
//#include <iostream>

const GLint WINDOW_WIDTH = 700;
const GLint WINDOW_HEIGHT = 700;
const GLfloat MOUSE_SENSITIVITY = 1.0f/200.0f;
GLuint program;

GLfloat projectionMatrix[16];

OpenGLCamera camera;
OpenGLObject rabbit;
int keyboardMap[256];
// vertex array object
Model *m, *m2, *tm;
// Reference to shader program
GLuint program;
GLuint tex1, tex2;
TextureData ttex; // terrain

void setKeyUp(unsigned char key, int x, int y);
void setKeyDown(unsigned char key, int x, int y);
void updateKeyboard();
void updateMouse(int x, int y);

void placeCameraOnGround() {
	int x = (int)(camera.position[0] + 0.5);
	int z = (int)(camera.position[2] + 0.5);
	int idx = (x + z * ttex.width)*3 + 1;
	setCameraPositionY(&camera, tm->vertexArray[idx] + 2.0);
}

void loadLightSources() {
	Point3D lightSourcesColorsArr[] = { {0.0f, 0.0f, 0.0f}, // Red light
		                             {0.0f, 0.0f, 0.0f}, // Green light
		                             {0.0f, 0.0f, 0.0f}, // Blue light
		                             {1.0f, 1.0f, 1.0f} }; // White light

	GLfloat specularExponent[] = {20.0, 20.0, 60.0, 200.0};
	GLint isDirectional[] = {1,1,1,1};

	Point3D lightSourcesDirectionsPositions[] = { {10.0f, 5.0f, 0.0f}, // Red light, positional
		                                   {0.0f, 5.0f, 10.0f}, // Green light, positional
		                                   {-1.0f, 0.0f, 0.0f}, // Blue light along X
		                                   {100.0f, 40.0f, 150.0f} }; // White light along Z

	glUniform3fv(glGetUniformLocation(program, "lightSourcesDirPosArr"), 4, &lightSourcesDirectionsPositions[0].x);
	glUniform3fv(glGetUniformLocation(program, "lightSourcesColorArr"), 4, &lightSourcesColorsArr[0].x);
	glUniform1fv(glGetUniformLocation(program, "specularExponent"), 4, specularExponent);
	glUniform1iv(glGetUniformLocation(program, "isDirectional"), 4, isDirectional);
}

Model* GenerateTerrain(TextureData *tex)
{
	int vertexCount = tex->width * tex->height;
	int triangleCount = (tex->width-1) * (tex->height-1) * 2;
	int x, z;
	
	GLfloat *vertexArray = malloc(sizeof(GLfloat) * 3 * vertexCount);
	GLfloat *normalArray = malloc(sizeof(GLfloat) * 3 * vertexCount);
	GLfloat *texCoordArray = malloc(sizeof(GLfloat) * 2 * vertexCount);
	GLuint *indexArray = malloc(sizeof(GLuint) * triangleCount*3);
	
	printf("bpp %d\n", tex->bpp);
	for (x = 0; x < tex->width; x++)
		for (z = 0; z < tex->height; z++)
		{
// Vertex array. You need to scale this properly
			vertexArray[(x + z * tex->width)*3 + 0] = x / 1.0;
			vertexArray[(x + z * tex->width)*3 + 1] = tex->imageData[(x + z * tex->width) * (tex->bpp/8)] / 20.0;
			vertexArray[(x + z * tex->width)*3 + 2] = z / 1.0;
// Texture coordinates. You may want to scale them.
			texCoordArray[(x + z * tex->width)*2 + 0] =  10.0*(float)x / tex->width;
			texCoordArray[(x + z * tex->width)*2 + 1] =  10.0*(float)z / tex->height;
		}

	// Normal vectors. You need to calculate these.
	for (x = 1; x < tex->width - 1; x++)
		for (z = 1; z < tex->height - 1; z++)
		{
			GLuint x1, x2, x3, z1, z2, z3;
			x1 = x-1;	z1 = z-1;
			x2 = x;		z2 = z+1;
			x3 = x+1;	z3 = z;

			Point3D p1 = {vertexArray[(x1 + z1 * tex->width)*3 + 0],
					vertexArray[(x1 + z1 * tex->width)*3 + 1],
					vertexArray[(x1 + z1 * tex->width)*3 + 2]};
			Point3D p2 = {vertexArray[(x2 + z2 * tex->width)*3 + 0],
					vertexArray[(x2 + z2 * tex->width)*3 + 1],
					vertexArray[(x2 + z2 * tex->width)*3 + 2]};
			Point3D p3 = {vertexArray[(x3 + z3 * tex->width)*3 + 0],
					vertexArray[(x3 + z3 * tex->width)*3 + 1],
					vertexArray[(x3 + z3 * tex->width)*3 + 2]};

			Point3D v1, v2, n;

			VectorSub(&p2, &p1, &v1);
			VectorSub(&p3, &p1, &v2);

			CrossProduct(&v1, &v2, &n);			

			normalArray[(x + z * tex->width)*3 + 0] = n.x;
			normalArray[(x + z * tex->width)*3 + 1] = n.y;
			normalArray[(x + z * tex->width)*3 + 2] = n.z;
		}
	
	
	for (x = 0; x < tex->width; x++)
	{
		normalArray[(x + 0 * tex->width)*3 + 0] = normalArray[(x + 1 * tex->width)*3 + 0];
		normalArray[(x + 0 * tex->width)*3 + 1] = normalArray[(x + 1 * tex->width)*3 + 1];
		normalArray[(x + 0 * tex->width)*3 + 2] = normalArray[(x + 1 * tex->width)*3 + 2];
	}
	
	for (x = 0; x < tex->width; x++)
	{
		normalArray[(x + tex->height-1 * tex->width)*3 + 0] = normalArray[(x + tex->height-2 * tex->width)*3 + 0];
		normalArray[(x + tex->height-1 * tex->width)*3 + 1] = normalArray[(x + tex->height-2 * tex->width)*3 + 1];
		normalArray[(x + tex->height-1 * tex->width)*3 + 2] = normalArray[(x + tex->height-2 * tex->width)*3 + 2];
	}
	
	for (z = 0; z < tex->height; z++)
	{
		normalArray[(0 + z * tex->width)*3 + 0] = normalArray[(1 + z * tex->width)*3 + 0];
		normalArray[(0 + z * tex->width)*3 + 1] = normalArray[(1 + z * tex->width)*3 + 1];
		normalArray[(0 + z * tex->width)*3 + 2] = normalArray[(1 + z * tex->width)*3 + 2];
	}
	
	for (z = 0; z < tex->height; z++)
	{
		normalArray[(tex->width-1 + z * tex->width)*3 + 0] = normalArray[(tex->width-2 + z * tex->width)*3 + 0];
		normalArray[(tex->width-1 + z * tex->width)*3 + 1] = normalArray[(tex->width-2 + z * tex->width)*3 + 1];
		normalArray[(tex->width-1 + z * tex->width)*3 + 2] = normalArray[(tex->width-2 + z * tex->width)*3 + 2];
	}
			
	

	for (x = 0; x < tex->width-1; x++)
		for (z = 0; z < tex->height-1; z++)
		{
		// Triangle 1
			indexArray[(x + z * (tex->width-1))*6 + 0] = x + z * tex->width;
			indexArray[(x + z * (tex->width-1))*6 + 1] = x + (z+1) * tex->width;
			indexArray[(x + z * (tex->width-1))*6 + 2] = x+1 + z * tex->width;
		// Triangle 2
			indexArray[(x + z * (tex->width-1))*6 + 3] = x+1 + z * tex->width;
			indexArray[(x + z * (tex->width-1))*6 + 4] = x + (z+1) * tex->width;
			indexArray[(x + z * (tex->width-1))*6 + 5] = x+1 + (z+1) * tex->width;
		}
	// End of terrain generation
	
	// Create Model and upload to GPU:

	Model* model = LoadDataToModel(
			vertexArray,
			normalArray,
			texCoordArray,
			NULL,
			indexArray,
			vertexCount,
			triangleCount*3);

	return model;
}

void init(void)
{

	// GL inits
	glClearColor(0.2,0.2,0.5,0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	program = loadShaders("terrain.vert", "terrain.frag");
	printError("GL inits");

	frustum(-0.2, 0.2, -0.2, 0.2, 0.1, 500.0, projectionMatrix);

	loadLightSources();

	// Load and compile shader
	glUseProgram(program);
	printError("init shader");
	
	glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, GL_TRUE, projectionMatrix);
	glUniform1i(glGetUniformLocation(program, "tex"), 0); // Texture unit 0
	LoadTGATextureSimple("grass.tga", &tex1);
	
// Load terrain data
	
	LoadTGATexture("fft-terrain.tga", &ttex);
	tm = GenerateTerrain(&ttex);

	rabbit = createOpenGLObject(LoadModelPlus("bunnyplus.obj"));
	addTextureToObject(&rabbit, tex1);
	setObjectPosition(&rabbit, 100.0, 50.0, 100.0);
	setObjectScaling(&rabbit, 30.0, 30.0, 30.0);
	
	createOpenGLCamera(&camera);
	setCameraPosition(&camera, 200, 20, 200);
	setCameraDirection3(&camera, 0, 0, -1);

	for (int i=0; i<256; i++)
		keyboardMap[i] = 0;

	printError("init terrain");
}

void display(void)
{
	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	GLfloat modelMatrix[16];
	GLfloat* camMatrix;
	
	printError("pre display");
	
	glUseProgram(program);

	// Build matrix
	
	IdentityMatrix(modelMatrix);
	camMatrix = camera.cameraMatrix;	

	glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, modelMatrix);
	glUniformMatrix4fv(glGetUniformLocation(program, "camMatrix"), 1, GL_TRUE, camMatrix);
	
	glBindTexture(GL_TEXTURE_2D, tex1);		// Bind Our Texture tex1
	DrawModel(tm, program, "inPosition", "inNormal", "inTexCoord");
	drawObject(&rabbit, program);
	DrawModel(rabbit.model, program, "inPosition", "inNormal", "inTexCoord");

	printError("display 2");
	
	glutSwapBuffers();
}

void timer(int i)
{
	glutTimerFunc(20, &timer, i);
	updateKeyboard();
	//placeCameraOnGround();
	updateCamera(&camera);
	updateObject(&rabbit, i);
	char s[1024];
	sprintf(s, "X=[%d] Y=[%d] Z=[%d]", (int)camera.position[0], (int)camera.position[1], (int)camera.position[2]);
	glutSetWindowTitle(s);
	//printf(s);
	glutPostRedisplay();
}

void setKeyUp(unsigned char key, int x, int y) {
	keyboardMap[key] = 0;
}

void setKeyDown(unsigned char key, int x, int y) {
	keyboardMap[key] = 1;
}

void updateKeyboard() {
	float speed = 0.6;
	if (keyboardMap['W'] == 1 || keyboardMap['w'] == 1) {
		moveCamera(&camera, 0, 0, -speed);
	} else if (keyboardMap['S'] == 1 || keyboardMap['s'] == 1) {
		moveCamera(&camera, 0, 0, speed);
	} 

	if (keyboardMap['A'] == 1 || keyboardMap['a'] == 1) {
		moveCamera(&camera, -speed, 0, 0);
	} else if (keyboardMap['D'] == 1 || keyboardMap['d'] == 1) {
		moveCamera(&camera, speed, 0, 0);
	}

	if (keyboardMap[32] == 1) {
		moveCamera(&camera, 0, speed*3, 0);
	} else if (keyboardMap['>'] == 1 || keyboardMap['<'] == 1) {
		moveCamera(&camera, 0, -speed*3, 0);
	}
}

void updateMouse(int x, int y) {
	//GLfloat dx = x - WINDOW_WIDTH/2;
	//GLfloat dy = y - WINDOW_HEIGHT/2;
	//glutWarpPointer(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	setCameraDirection2(&camera, y*MOUSE_SENSITIVITY, x*MOUSE_SENSITIVITY);
}

int main(int argc, char **argv)
{
    //std::cout << "hello world" << std::endl;
	srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize (WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow ("TSBK07 Lab 4");
	glutDisplayFunc(display);
	glutPassiveMotionFunc(updateMouse);
	glutKeyboardFunc(setKeyDown);
	glutKeyboardUpFunc(setKeyUp);
	init();
	glutTimerFunc(20, &timer, 0);

	glutMainLoop();
	exit(0);
}
