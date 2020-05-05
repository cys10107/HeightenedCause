#pragma once
#include "ofMain.h"
enum state { LEFT = 0, RIGHT = 1 };
class Wall
{
private:
	ofVec2f _posA;    //up
	ofVec2f _posB;    //down
	ofVec2f _movedpx = { 0, 0 };

public:
	Wall();
	Wall(ofVec2f inA, ofVec2f inB, state inDir);
	Wall(float y1, float y2, float x, state inDir);
	~Wall();
	state direction;

	//for file output
	ofVec2f getPosA() { return this->_posA; }
	ofVec2f getPosB() { return this->_posB; }

	//methods
	void camMove(float x = 0, float y = 0) { this->_movedpx.x += x; this->_movedpx.y += y; };
	void display();
	float getX() { return this->_posA.x; }
	bool detect(ofVec2f inPos);
};