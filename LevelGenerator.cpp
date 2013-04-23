//
//  LevelGenerator.cpp
//  OpenGLGLUTApp
//
//  Created by Simon Borgenvall on 2013-04-22.
//
//

#include "LevelGenerator.h"

bool LevelGenerator::fileExists(const std::string &fileName)
{
	std::ifstream ifs(fileName.c_str());
	if (!ifs || ifs.bad())
		return false;
	return true;
}

bool LevelGenerator::open(const std::string &fileName)
{
	if(!fileExists(fileName))
		return false;
	close();
	_fileStream = new std::ifstream(fileName.c_str());
	if (!*_fileStream || _fileStream->bad()) {
		close();
		return false;
	}
	_fileName = fileName;
	return true;
}

void LevelGenerator::close()
{
	if (_fileStream) {
		delete _fileStream;
		_fileStream = 0;
		_fileName = "";
	}
}

void LevelGenerator::readMap()
{
	_fileStream->getline(_buffer, _buffSize);
	std::cout << _buffer << std::endl;
}

std::string& LevelGenerator::getFileName()
{
	return _fileName;
}


LevelGenerator::LevelGenerator() : _buffSize(UINT_MAX)
{}