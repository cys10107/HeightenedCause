#pragma once
#include "ofMain.h"

class Ceiling
{
private:
	ofVec2f _posA;
	ofVec2f _posB;
	ofVec2f _movedpx = { 0, 0 };

public:
	Ceiling(ofVec2f inA, ofVec2f inB);
	Ceiling(float x1 = 100, float x2 = 500, float y = 400);
	~Ceiling();

	//for file output
	ofVec2f getPosA() { return this->_posA; }
	ofVec2f getPosB() { return this->_posB; }

	//methods
	void camMove(float x = 0, float y = 0) { this->_movedpx.x += x; this->_movedpx.y += y; }
	void display();
	float getHeight() { return this->_posA.y; }
	bool detect(ofVec2f inPos);
	float getDistance(ofVec2f inPos);
};