//
//  GameObject.h
//  OpenGLGLUTApp
//
//  Created by Marcus Johansson on 4/10/13.
//
//

#ifndef __OpenGLGLUTApp__GameObject__
#define __OpenGLGLUTApp__GameObject__

#include "Renderable.h"
#include "Body.h"
#include "BoundingBox.h"

class GameObject : virtual public Renderable, virtual public Body {
public:
    GameObject(BoundingBox boundingBox) : Renderable(), Body(), _boundingBox(boundingBox) {}
    virtual ~GameObject() {}
	
	BoundingBox getBoundingBox();
	virtual std::string getType() = 0;
    
protected:
    virtual mat4 getModelTransformationMatrix();
    
private:
    BoundingBox _boundingBox;
    
};

#endif /* defined(__OpenGLGLUTApp__GameObject__) */
