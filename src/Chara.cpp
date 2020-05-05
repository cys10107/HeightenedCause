#include "Chara.h"
bool temp = false;
int jumpCounter = 0;

Chara::Chara()
{
	this->_pos = { 100, 100 };
	this->_vx = 0;
	this->_vy = 0;
	this->_ax = 0;
	this->_ay = ACCELERATION;
	this->_dir = true;
}

Chara::Chara(ofVec2f inPos)
{
	this->_pos = inPos;
	this->_vx = 0;
	this->_vy = 0;
	this->_ax = 0;
	this->_ay = ACCELERATION;
	this->_dir = true;
}

Chara::~Chara()
{
}

void Chara::keyReactions(bool can_short_jump)
{
	//key reactions

	//left & right
	if (this->a_pressed)
	{
		this->_vx -= 1;
	}
	if (this->d_pressed)
	{
		this->_vx += 1;
	}
	if (this->a_pressed && this->d_pressed)
	{
		this->_vx += -(this->_vx - 0) / 5;
	}

	//cout << this->can_jump << endl;
	//chaaaaaaaaaaarge
	if (!temp && this->s_pressed && this->w_pressed && this->on_floor && this->can_jump)
	{
		this->charging = true;
		jumpCounter += 1;
	}
	else
	{
		this->charging = false;
		jumpCounter = 0;
	}

	//jump
	if (this->can_jump && (jumpCounter >= CHARGE_TIME || jumpCounter == 0))
	{
		if (!temp && w_pressed)
		{
			//this->can_jump = true;

			if (this->on_floor)
			{
				if (this->w_pressed)
				{
					if (jumpCounter >= CHARGE_TIME)
					{
						this->_vy = -LEAP_FORCE - 4;
						jumpCounter = 0;
					}
					else
						this->_vy = -LEAP_FORCE;
					this->jumped = true;
					//this->can_jump = false;
				}
			}
		}
		if (!this->on_floor)
		{
			if (this->_vy >= 0)
			{
				this->jumped = false;
			}
			if (can_short_jump)
			{
				if (!this->w_pressed && this->jumped)
				{
					this->_vy = -(LEAP_FORCE / 6);
					this->jumped = false;
				}
			}
		}
		
		temp = this->w_pressed;
	
	}

	//crouch
	if (this->s_pressed)
	{
		this->_crouch = true;
		if (this->on_floor)
			this->_vx += -(this->_vx - 0) / 2;
	}
	else if (this->_crouch && this->is_ceiling_top)
	{
		this->_crouch = true;
		//this->can_jump = false;
		if (this->on_floor)
			this->_vx += -(this->_vx - 0) / 2;
	}
	else
	{
		this->_crouch = false;
		this->can_jump = true;
	}

	
}

void Chara::processMovements()
{
	//process movements

	//acceleration
	this->_vy += this->_ay;
	this->_vx += this->_ax;
	//cout << this->_vy << endl;
	//position shift
	this->_pos.x += this->_vx;
	this->_pos.y += this->_vy;
	

	//dir toggle
	if (this->_vx > 0)
		this->_dir = true;
	else
		this->_dir = false;
	//max speed
	if (this->_vx > WALK_MAX_SPEED)
		this->_vx = WALK_MAX_SPEED;
	else if (this->_vx < -WALK_MAX_SPEED)
		this->_vx = -WALK_MAX_SPEED;
	//friction
	if (this->on_floor && !(this->a_pressed || this->d_pressed))
	{
		if (fabs(this->_vx) - this->friction >= 0)
			this->_vx -= (int(this->_dir) * 2 - 1) * this->friction;
		else
			this->_vx = 0;
	}
}

void Chara::display()
{
	//cout << this->_pos.x << '\t' << this->_pos.y << endl;
	ofVec2f temp = { this->_pos.x + this->_movedpx.x, this->_pos.y + this->_movedpx.y };
	if (!this->_crouch)
	{
		ofSetColor(150, 150, 150);
		ofDrawRectangle(temp, CHARACTER_WIDTH, -CHARACTER_HEIGHT);
		ofSetColor(0, 0, 0);
	}
	else
	{
		ofSetColor(150, 150, 150);
		ofDrawRectangle(temp, CHARACTER_WIDTH, -CROUCH_HEIGHT);
		ofSetColor(0, 0, 0);
	}
	if (this->charging)
	{
		double r = jumpCounter / 100.0;
		temp.y -= CROUCH_HEIGHT + 5;
		ofSetColor((r * 155) + 100, 150, 150);
		ofDrawRectangle(temp, CHARACTER_WIDTH * r, -5);
		ofSetColor(0, 0, 0);
	}
}
