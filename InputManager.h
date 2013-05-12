//
//  InputManager.h
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 5/10/13.
//
//

#ifndef __OpenGLGLUTApp__InputManager__
#define __OpenGLGLUTApp__InputManager__

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include "MicroGlut.h"
#endif

class InputManager
{
public:
    static InputManager& getInstance();
    
    void init();
    void update(unsigned int dtime);
    
    int getMouseSpeedX();
    int getMouseSpeedY();
	int getScrollSpeed();
    
    bool isKeyDown(unsigned char key);
    
    friend class SigmaGameEngine;
    
private:
    InputManager();
    InputManager(const InputManager&);
    InputManager& operator=(const InputManager&);
    
    // SigmaGameEngine reaches these functions through friendship
    void setKeyUp(unsigned char key);
    void setKeyDown(unsigned char key);
    void updateMouse(int button, int state, int x, int y);
    void updateMouse(int x, int y);
    
    unsigned int SDL_WINDOW_WIDTH = 500;
    unsigned int SDL_WINDOW_HEIGHT = 500;
    
    unsigned char keyboardMap[256];
    int mouse_speed_x;
    int mouse_speed_y;
	int scroll_speed;
};

#endif /* defined(__OpenGLGLUTApp__InputManager__) */
