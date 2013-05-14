//
//  InputManager.cpp
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 5/10/13.
//
//

#include <iostream>

#include "SigmaGameEngine.h"
#include "InputManager.h"
#include <SDL/SDL.h>

InputManager& InputManager::getInstance()
{
    static InputManager instance;
    return instance;
}

InputManager::InputManager()
{
    for (int i=0; i<256; ++i) keyboardMap[i] = 0;
}

InputManager::InputManager(const InputManager&) {}

InputManager& InputManager::operator=(const InputManager&) {return *this;}

void InputManager::init()
{
    if (SDL_Init( SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    
    SDL_Surface* sdl_display = SDL_SetVideoMode(SDL_WINDOW_WIDTH,
                                                SDL_WINDOW_HEIGHT,
                                                16, SDL_SWSURFACE);
    
    SDL_WM_GrabInput(SDL_GRAB_ON);
    //SDL_ShowCursor(SDL_DISABLE);
}

void InputManager::update(unsigned int dtime)
{
    mouse_speed_x = mouse_speed_y = scroll_speed = 0;
    
    SDL_Event event;
    while( SDL_PollEvent( &event ) ){
        switch( event.type ){
            case SDL_KEYDOWN:
                switch( event.key.keysym.sym ){
                    case SDLK_w: keyboardMap['w'] = 1; break;
                    case SDLK_a: keyboardMap['a'] = 1; break;
                    case SDLK_s: keyboardMap['s'] = 1; break;
                    case SDLK_d: keyboardMap['d'] = 1; break;
                    case SDLK_SPACE: keyboardMap[' '] = 1; break;
                    case SDLK_LESS: keyboardMap['<'] = 1; break;
                    case SDLK_ESCAPE: SigmaGameEngine::getInstance().quit();
                    default: break;
                }
                break;
            case SDL_KEYUP:
                switch( event.key.keysym.sym ){
                    case SDLK_w: keyboardMap['w'] = 0; break;
                    case SDLK_a: keyboardMap['a'] = 0; break;
                    case SDLK_s: keyboardMap['s'] = 0; break;
                    case SDLK_d: keyboardMap['d'] = 0; break;
                    case SDLK_SPACE: keyboardMap[' '] = 0; break;
                    case SDLK_LESS: keyboardMap['<'] = 0; break;
                    default: break;
                }
                break;

            case SDL_MOUSEMOTION:
                mouse_speed_x += event.motion.xrel;
                mouse_speed_y += event.motion.yrel;
                break;
				
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button)
				{
				case SDL_BUTTON_WHEELUP:
						scroll_speed--;
					break;
				case SDL_BUTTON_WHEELDOWN:
						scroll_speed++;
					break;
				}
				break;
        }
    }
    
    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
    SDL_WarpMouse(SDL_WINDOW_WIDTH/2, SDL_WINDOW_HEIGHT/2);
    SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
    
}

int InputManager::getMouseSpeedX()
{
    return mouse_speed_x;
}

int InputManager::getMouseSpeedY()
{
    return mouse_speed_y;
}

int InputManager::getScrollSpeed()
{
	return scroll_speed;
}

bool InputManager::isKeyDown(unsigned char key)
{
    //std::cerr << "InputManager::isKeyDown\n";
    return keyboardMap[key] == 1;
}

void InputManager::setKeyUp(unsigned char key)
{
    std::cerr << "InputManager::setKeyUp\n";
    keyboardMap[key] = 0;
}

void InputManager::setKeyDown(unsigned char key)
{
    std::cerr << "InputManager::setKeyDown\n";
    keyboardMap[key] = 1;
}

void InputManager::updateMouse(int button, int state, int x, int y)
{
    std::cerr << "updateMouse(" << button << ", " << state << ", " << x << ", " << y << ")\n";
    //GLfloat dx = x - WINDOW_WIDTH/2;
	//GLfloat dy = y - WINDOW_HEIGHT/2;
	//glutWarpPointer(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	//setCameraDirection2(&camera, y*MOUSE_SENSITIVITY, x*MOUSE_SENSITIVITY);
    //SigmaGameEngine::getInstance().updateMouse(x, y);
}

void InputManager::updateMouse(int x, int y)
{
    std::cerr << "updateMouse(" << x << ", " << y << ")\n";
    glutWarpPointer(100, 100);
    //GLfloat dx = x - WINDOW_WIDTH/2;
	//GLfloat dy = y - WINDOW_HEIGHT/2;
	//glutWarpPointer(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	//setCameraDirection2(&camera, y*MOUSE_SENSITIVITY, x*MOUSE_SENSITIVITY);
}