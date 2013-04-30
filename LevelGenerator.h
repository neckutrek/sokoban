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
#include "GameObjectManager.h"
#include "GameObjectFactory.h"

class LevelGenerator
{
	
public:
	
	static LevelGenerator& getInstance()
	{
		static LevelGenerator instance;
		return instance;
	}
	
	bool fileExists(const std::string& fileName) const;
	void load(const std::string &fileName);
	std::string& getFileName();
	
protected:
	bool open(const std::string& fileName);
	void close();
	void read();
	void readMap();
	void readExtras();
	void generateMap();
	void applyExtras();
	
	//Ska detta ligga nån annanstans
	//bool generateComponent(GameComponent component, vec3 pos);
	
private:
	enum MapToken
	{
		EMPTY=0,
		WALL=1,
		PLATE=2,
		PLAYER=3,
		PLAYER_ON_PLATE=4,
		BLOCK=5,
		BLOCK_ON_PLATE=6
	};
	
	enum ExtraType
	{
		EMPTY_EXTRA=-1,
		TEST_EXTRA=0
	};
	
	struct Extra
	{
		ExtraType type;
		std::string value;
	};
	
	static const int MAX_LEVEL_WIDTH = 100;
	static const int MAX_LEVEL_HEIGHT = 100;
	static const int MAX_EXTRAS = 10;
	static const std::string CHAR_MAPPER;
	static const std::string EXTRA_MAPPER[];
	
	MapToken getMapToken(char token);
	ExtraType getExtraType(std::string extra);
	
	std::string _buffer;
	std::string _fileName;
	std::ifstream* _fileStream;
	MapToken _map[MAX_LEVEL_WIDTH*MAX_LEVEL_HEIGHT];
	int _mapWidth;
	int _mapHeight;
	Extra _extras[MAX_EXTRAS];
	
	LevelGenerator();
	LevelGenerator(const LevelGenerator&);
	LevelGenerator& operator=(const LevelGenerator&);
};

#endif /* defined(__OpenGLGLUTApp__LevelGenerator__) */
