#pragma once
#include "ofMain.h"
const float ACCELERATION = 0.72;   //1.0
const float LEAP_FORCE = 17;     //21    //current max height: 220.5, 295
const float CHARACTER_WIDTH = 30;   //30
const float CHARACTER_HEIGHT = 50;	//50 
const float CROUCH_HEIGHT = 35;		//35
const float WALL_SLIDE_SPEED = 0.7;	//0.7
const float WALLJUMP_HEIGHT = 15;	//10
const float WALLJUMP_SPEED = 7;	//7
const float WALK_MAX_SPEED = 4.5; //4.5  //horizontal max leap length = 189
const int CHARGE_TIME = 100;

//vt - at^2 / 2 

class Chara
{
private:
	ofVec2f _pos;
	float _vx, _vy, _ax, _ay;
	bool _dir, _crouch = false, charging = false;
	//for camera movements
	ofVec2f _movedpx = { 0, 0 };

	//for cpp tests and calculations
	int toggle = 0;
	int _counter = 0, _counter2 = 0;
	//int _jumps = 2;
	float friction = 3;

public:
	Chara();
	Chara(ofVec2f inPos);
	~Chara();

	//inline functions
	bool w_pressed = false, a_pressed = false, s_pressed = false, d_pressed = false, jumped = false, can_jump = false;
	bool on_wall_right = false, on_wall_left = false;
	bool on_floor = true;
	bool is_ceiling_top = false;

	ofVec2f getTRPos() {
		if (this->_crouch)
			return ofVec2f(this->_pos.x + CHARACTER_WIDTH, this->_pos.y - CROUCH_HEIGHT);
		else
			return ofVec2f(this->_pos.x + CHARACTER_WIDTH, this->_pos.y - CHARACTER_HEIGHT);
	}
	ofVec2f getTLPos() {
		if (this->_crouch)
			return ofVec2f(this->_pos.x, this->_pos.y - CROUCH_HEIGHT);
		else
			return ofVec2f(this->_pos.x, this->_pos.y - CHARACTER_HEIGHT);
	}

	ofVec2f getBRPos() { return ofVec2f(this->_pos.x + CHARACTER_WIDTH, this->_pos.y); }
	ofVec2f getBLPos() { return ofVec2f(this->_pos.x, this->_pos.y); }
	//float getVY() { return this->_vy; }
	void resetVY() { this->_vy = 0; }
	float getVY() { return this->_vy; }
	float getRelativeY() { return this->_pos.y + this->_movedpx.y; }
	float getRelativeX() { return this->_pos.x + this->_movedpx.x; }
	void setAY(float inA) { this->_ay = 0; }
	void resetAY() { this->_ay = ACCELERATION; }
	void setX(float inX) { this->_pos.x = inX; }
	void setVX(float inV) { this->_vx = inV; }
	void setY(float inY) { this->_pos.y = inY; }
	void setVY(float inVY) { this->_vy = inVY; }
	void camMove(float x = 0, float y = 0) { this->_movedpx.x += x; this->_movedpx.y += y; }

	//other functions
	void keyReactions(bool can_short_jump);
	void processMovements();
	void display();
};