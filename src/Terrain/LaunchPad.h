#pragma once
#include "ofMain.h"
#include <fstream>
const float LAUNCHPAD_WIDTH = 40;
const float LAUNCHPAD_HEIGHT = 20;

class LaunchPad
{
private:
	ofVec2f _pos;
	
	ofVec2f movedpx = { 0, 0 };

public:
	float _leapForce;
	LaunchPad(float inX = 100, float inY = 100, float inLF = 100);
	~LaunchPad();

	bool detect(ofVec2f inPos);

	void fileOutput(ofstream& fout);

	void camMove(float x, float y) { this->movedpx.x += x; this->movedpx.y += y; }
	void display();
};
