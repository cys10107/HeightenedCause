#pragma once
#include "ofMain.h"
#include <fstream>
const int CHECKPOINT_WIDTH = 30;
const int CHECKPOINT_HEIGHT = 60;

class CheckPoint
{
private:
	ofVec2f _pos;
	bool _is_touched = false;
	ofVec2f movedpx = { 0, 0 };
	bool _can_touch = true;

public:
	CheckPoint(ofVec2f inPos);
	~CheckPoint();

	void fileOutput(ofstream& fout);

	ofVec2f getPos() { return this->_pos; }
	bool test() { return this->_is_touched; }
	bool detect(ofVec2f inPos);
	void display();
	void camMove(float x, float y) { this->movedpx.x += x; this->movedpx.y += y; }
};