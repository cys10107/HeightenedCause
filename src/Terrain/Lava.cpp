#include "Lava.h"

Lava::Lava(ofVec2f inPos, float inW, float inH)
{
	this->_pos = inPos;
	this->_w = inW;
	this->_h = inH;
}

Lava::~Lava()
{
}

bool Lava::detect(ofVec2f inPos)
{
	if (inPos.x < this->_pos.x + this->_w && inPos.x > this->_pos.x && inPos.y > this->_pos.y - this->_h && inPos.y < this->_pos.y)
		return true;
	else
		return false;
}

void Lava::fileOutput(ofstream& fout)
{
	fout << this->_pos.x << " " << this->_pos.y << " " << this->_w << " " << this->_h;
	fout << endl;
}

void Lava::display()
{
	ofVec2f temp = { this->_pos.x + this->movedpx.x, this->_pos.y + this->movedpx.y };
	ofSetColor(255, 0, 0);
	ofDrawRectangle(temp, this->_w, -this->_h);
	ofSetColor(255, 255, 255);
}