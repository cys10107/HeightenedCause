#pragma once
#include "ofMain.h"

class FloorLine
{
private:
	ofVec2f _posA;
	ofVec2f _posB;
	ofVec2f _movedpx = { 0, 0 };

public:
	FloorLine(ofVec2f inA, ofVec2f inB);
	FloorLine(float x1 = 100, float x2 = 500, float y = 400);
	~FloorLine();

	//for file output
	ofVec2f getPosA() { return this->_posA; }
	ofVec2f getPosB() { return this->_posB; }

	//methods
	void camMove(float x = 0, float y = 0) { this->_movedpx.x += x; this->_movedpx.y += y; }
	void display();
	float getHeight() { return this->_posA.y; }
	bool detect(ofVec2f inPos);
};