#pragma once
#include "ofMain.h"
#include <fstream>

class GoalArea
{
private:
	ofVec2f _pos;
	float _w, _h;
	bool is_exsist = true;
	bool _temp = false;
	ofVec2f movedpx = { 0, 0 };

public:
	GoalArea(ofVec2f inPos = { 100, 100 }, float inW = 50.0, float inH = 50.0);
	GoalArea(bool inBool);
	~GoalArea();
	bool w_pressed = false;
	
	//for file output
	void output(ofstream& fout) { fout << this->_pos.x << " " << this->_pos.y << " " << this->_w << " " << this->_h << endl; }

	bool exsist();

	void camMove(float x, float y) { this->movedpx.x += x; this->movedpx.y += y; }
	void update();
	bool WinTest(ofVec2f inPosA);
	void display();
};