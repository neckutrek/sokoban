//
//  GameComponent.h
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/4/13.
//
//

#ifndef __OpenGLGLUTApp__GameComponent__
#define __OpenGLGLUTApp__GameComponent__

class GameComponent
{
public:
    GameComponent() : _active(true) {}
    
    int update(unsigned int time) {
        if (_active) {
            update_function(time);
        }
        return 0;
    }
    virtual int update_function(unsigned int time) = 0;
    
    inline void pause() {_active = false;}
    inline void activate() {_active = true;}
    
private:
    bool _active;
    
};

#endif /* defined(__OpenGLGLUTApp__GameComponent__) */
