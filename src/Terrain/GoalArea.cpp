#include "GoalArea.h"

GoalArea::GoalArea(ofVec2f inPos, float inW, float inH)
{
	this->_pos = inPos;
	this->_w = inW;
	this->_h = inH;
}

GoalArea::GoalArea(bool inBool)
{
	this->_pos = { -10000, -10000 };
	this->_w = this->_h = 0;
	this->is_exsist = inBool;
}

GoalArea::~GoalArea()
{
}

bool GoalArea::exsist()
{
	if (this->is_exsist)
		return true;
	else
		return false;
}

void GoalArea::update()
{
	this->_temp = false;
}

bool GoalArea::WinTest(ofVec2f inPos)
{
	if ((inPos.x < this->_pos.x + this->_w && inPos.x > this->_pos.x) && inPos.y > this->_pos.y - this->_h && inPos.y < this->_pos.y)
	{
		return true;
	}
	else
		return false;
}

void GoalArea::display()
{
	ofVec2f temp = { this->_pos.x + this->movedpx.x, this->_pos.y + this->movedpx.y };
	ofSetColor(0, 255, 0);
	ofDrawRectangle(temp, this->_w, -this->_h);
	ofSetColor(255, 255, 255);
	this->_temp = this->w_pressed;
}