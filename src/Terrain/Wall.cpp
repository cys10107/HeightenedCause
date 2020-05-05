#include "Wall.h"

Wall::Wall()
{
	this->_posA = this->_posB = { 0, 0 };
}

Wall::Wall(ofVec2f inA, ofVec2f inB, state inDir)
{
	if (inA.y < inB.y)
	{
		this->_posA = inA;
		this->_posB = inB;
		this->_posA.x = this->_posB.x = inA.x;
		this->direction = inDir;
	}
	else
	{
		this->_posA = inB;
		this->_posB = inB;
		this->_posA.x = this->_posB.x = inA.x;
		this->direction = inDir;
	}
}

Wall::Wall(float y1, float y2, float x, state inDir)
{
	if (y2 > y1)
	{
		this->_posA.y = y1;
		this->_posB.y = y2;
		this->_posA.x = this->_posB.x = x;
		this->direction = inDir;
	}
	else
	{
		this->_posA.y = y2;
		this->_posB.y = y1;
		this->_posA.x = this->_posB.x = x;
		this->direction = inDir;
	}
}

Wall::~Wall()
{
}

void Wall::display()
{
	ofVec2f tempA = { this->_posA.x + this->_movedpx.x, this->_posA.y + this->_movedpx.y };
	ofVec2f tempB = { this->_posB.x + this->_movedpx.x, this->_posB.y + this->_movedpx.y };
	ofSetColor(0, 0, 0);
	ofDrawLine(tempA, tempB);
}

bool Wall::detect(ofVec2f inPos)
{
	if (this->direction == LEFT)
	{
		if ((inPos.y >= this->_posA.y && inPos.y <= this->_posB.y) && inPos.x >= this->_posA.x)
			return true;
		else
			return false;
	}
	else
	{
		if ((inPos.y >= this->_posA.y && inPos.y <= this->_posB.y) && inPos.x <= this->_posA.x)
			return true;
		else
			return false;
	}
}
