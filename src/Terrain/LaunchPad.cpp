#include "LaunchPad.h"

LaunchPad::LaunchPad(float inX, float inY, float inLF)
{
	this->_pos = { inX, inY };
	this->_leapForce = inLF;
}

LaunchPad::~LaunchPad()
{
}

bool LaunchPad::detect(ofVec2f inPos)
{
	if ((inPos.x > this->_pos.x && inPos.x < this->_pos.x + LAUNCHPAD_WIDTH) && (inPos.y >= (this->_pos.y - LAUNCHPAD_HEIGHT) && inPos.y <= this->_pos.y - (LAUNCHPAD_HEIGHT / 8)))
	{
		return true;
	}
	else
		return false;
}

void LaunchPad::fileOutput(ofstream& fout)
{
	fout << this->_pos.x << " " << this->_pos.y << " " << this->_leapForce << endl;
}

void LaunchPad::display()
{
	ofVec2f temp = { this->_pos.x + this->movedpx.x, this->_pos.y + this->movedpx.y };
	ofSetColor(0, 0, 255);
	ofDrawRectangle(temp, LAUNCHPAD_WIDTH, -LAUNCHPAD_HEIGHT);
}
