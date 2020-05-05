#include "CheckPoint.h"

CheckPoint::CheckPoint(ofVec2f inPos)
{
	this->_pos = inPos;
}

CheckPoint::~CheckPoint()
{
}

void CheckPoint::fileOutput(ofstream& fout)
{
	fout << this->_pos.x << ' ' << this->_pos.y << endl;
}

bool CheckPoint::detect(ofVec2f inPos)
{
	if (this->_can_touch && (inPos.x < this->_pos.x + CHECKPOINT_WIDTH && inPos.x > this->_pos.x&& inPos.y < this->_pos.y && inPos.y > this->_pos.y - CHECKPOINT_HEIGHT))
	{
		this->_is_touched = true;
		this->_can_touch = false;
		return true;
	}
	else
	{
		//this->_is_touched = false;
		return false;
	}
}

void CheckPoint::display()
{
	ofVec2f temp = { this->_pos.x + this->movedpx.x, this->_pos.y + this->movedpx.y };
	if (!this->_is_touched)
	{
		ofSetColor(255, 150, 0);
	}
	else
	{
		ofSetColor(70, 255, 255);
	}
	ofDrawRectangle(temp, CHECKPOINT_WIDTH, -CHECKPOINT_HEIGHT);
	ofSetColor(255, 255, 255);
}
