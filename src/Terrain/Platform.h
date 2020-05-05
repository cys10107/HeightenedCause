#pragma once
#include "Wall.h"
#include "Ceiling.h"
#include "FloorLine.h"
#include <fstream>

class Platform
{
private:
	float _w = 150, _h = 20;
	ofVec2f _pos;
	void resetLines();

public:
	FloorLine floor;
	Ceiling ceiling;
	Wall wallLeft, wallRight;

	Platform();
	Platform(ofVec2f inPos,float inW, float inH);
	~Platform();
	
	//for file output
	void fileOutput(ofstream& fout);

	//for file input
	void fileInput(ifstream& fin);

	//for getting information
	float getFloorHeight() { return this->_pos.y - this->_h; }
	float getCeilingHeight() { return this->_pos.y; }
	float getWallLeftX() { return this->_pos.x; }
	float getWallRight() { return this->_pos.x + this->_w; }

	//for detect
	bool floorDetect(ofVec2f inPos) { return this->floor.detect(inPos); }
	bool ceilingDetect(ofVec2f inPos) { return this->ceiling.detect(inPos); }
	bool wallLeftDetect(ofVec2f inPos) { return this->wallLeft.detect(inPos); }
	bool wallRightDetect(ofVec2f inPos) { return this->wallRight.detect(inPos); }

	//big methods
	void camMove(float x = 0, float y = 0);
	void display();
};