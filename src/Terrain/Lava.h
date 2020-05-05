#pragma once
#include "ofMain.h"
#include <fstream>

class Lava
{
private:
	ofVec2f _pos;
	float _w, _h;
	ofVec2f movedpx = { 0, 0 };

public:
	Lava(ofVec2f inPos, float inW, float inH);
	~Lava();

	bool detect(ofVec2f inPos);

	void fileOutput(ofstream& fout);

	void camMove(float x, float y) { this->movedpx.x += x; this->movedpx.y += y; }
	void display();
};