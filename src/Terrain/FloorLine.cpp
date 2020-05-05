#include "FloorLine.h"

FloorLine::FloorLine(ofVec2f inA, ofVec2f inB)
{
	if (inA.x > inB.x)
	{
		this->_posA = inB;
		this->_posB = inA;
	}
	else
	{
		this->_posA = inA;
		this->_posB = inB;
	}
}

FloorLine::FloorLine(float x1, float x2, float y)
{
	if (x1 > x2)
	{
		this->_posA = { x2, y };
		this->_posB = { x1, y };
	}
	else
	{
		this->_posA = { x1, y };
		this->_posB = { x2, y };
	}
}

FloorLine::~FloorLine()
{
}

void FloorLine::display()
{
	ofVec2f tempA = { this->_posA.x + this->_movedpx.x, this->_posA.y + this->_movedpx.y };
	ofVec2f tempB = { this->_posB.x + this->_movedpx.x, this->_posB.y + this->_movedpx.y };
	ofSetColor(0, 0, 0);
	ofDrawLine(tempA, tempB);
}

bool FloorLine::detect(ofVec2f inPos)
{
	if ((inPos.x < this->_posB.x && inPos.x > this->_posA.x) && inPos.y >= this->_posA.y - 1)
		return true;
	else
		return false;
}
