//
//  Player.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-30.
//
//

#ifndef __OpenGLGLUTApp__Player__
#define __OpenGLGLUTApp__Player__

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "GameObjectManager.h"
#include "GO_Block.h"

class GO_Player : public GameObject
{
public:
	GO_Player(vec3 pos);
	~GO_Player() {}
	std::string getType();
	
	virtual void setRot(GLfloat x, GLfloat y, GLfloat z, GLfloat a);
	
	void setRelPosToVector(vec3 v, vec3 pos);
	void push();
	
	virtual int update_function(unsigned int time);
	
protected:
	
private:
	
	class GO_PlayerBase : public GameObject
	{
	public:
		GO_PlayerBase();
		~GO_PlayerBase() {}
		std::string getType();
		
	protected:
		
	private:
		
	};
	
	GO_PlayerBase* _playerBase;
    int my_light_index;
	GLfloat _myRot;
	
};

#endif /* defined(__OpenGLGLUTApp__Player__) */
