#include "Platform.h"

Platform::Platform()
{
}

Platform::Platform(ofVec2f inPos, float inW, float inH)
{
	this->_w = inW;
	this->_h = inH;
	this->_pos = inPos;
	this->floor = FloorLine(this->_pos.x, this->_pos.x + this->_w, this->_pos.y - this->_h);
	this->ceiling = Ceiling(this->_pos.x, this->_pos.x + this->_w, this->_pos.y);
	this->wallLeft = Wall(this->_pos.y - this->_h, this->_pos.y, this->_pos.x, LEFT);
	this->wallRight = Wall(this->_pos.y - this->_h, this->_pos.y, this->_pos.x + this->_w, RIGHT);
}

Platform::~Platform()
{
}

void Platform::resetLines()
{
	this->floor = FloorLine(this->_pos.x, this->_pos.x + this->_w, this->_pos.y - this->_h);
	this->ceiling = Ceiling(this->_pos.x, this->_pos.x + this->_w, this->_pos.y);
	this->wallLeft = Wall(this->_pos.y - this->_h, this->_pos.y, this->_pos.x, LEFT);
	this->wallRight = Wall(this->_pos.y - this->_h, this->_pos.y, this->_pos.x + this->_w, RIGHT);
}

void Platform::fileOutput(ofstream& fout)
{
	fout << this->_pos.x << ' ' << this->_pos.y << ' '
		<< this->_w << ' ' << this->_h << endl;
}

void Platform::fileInput(ifstream& fin)
{
	float inX, inY, inW, inH;
	fin >> inX;
	fin >> inY;
	fin >> inW;
	fin >> inH;
	this->_pos = { inX, inY };
	this->_w = inW;
	this->_h = inH;
	this->resetLines();
}

void Platform::camMove(float x, float y)
{
	this->floor.camMove(x, y);
	this->ceiling.camMove(x, y);
	this->wallLeft.camMove(x, y);
	this->wallRight.camMove(x, y);
}

void Platform::display()
{
	this->floor.display();
	this->ceiling.display();
	this->wallRight.display();
	this->wallLeft.display();
}