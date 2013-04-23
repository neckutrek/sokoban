//
//  LevelGenerator.h
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-22.
//
//

#ifndef __OpenGLGLUTApp__LevelGenerator__
#define __OpenGLGLUTApp__LevelGenerator__

#include <iostream>
#include <fstream>
#include "GameComponent.h"
#include "VectorUtils3Addons.h"

class LevelGenerator
{
	
public:
	static LevelGenerator& getInstance()
	{
		static LevelGenerator instance;
		return instance;
	}
	
	bool open(const std::string& fileName);
	void close();
	bool fileExists(const std::string& fileName);
	void readMap();
	void readExtras();
	std::string& getFileName();
	
protected:
	unsigned getNextMapLine();
	char getMapToken();
	
	//Ska detta ligga nån annanstans
	//bool generateComponent(GameComponent component, vec3 pos);
	
private:
	char* _buffer;
	std::string _fileName;
	std::ifstream* _fileStream;
	LevelGenerator();
	LevelGenerator(const LevelGenerator&);
	LevelGenerator& operator=(const LevelGenerator&);

	
};

#endif /* defined(__OpenGLGLUTApp__LevelGenerator__) */
