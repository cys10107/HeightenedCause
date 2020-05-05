#pragma once
#include "Chara.h"
#include "Terrain/FloorLine.h"
#include "Terrain/Ceiling.h"
#include "Terrain/Wall.h"
#include "Terrain/Platform.h"
#include "Terrain/GoalArea.h"
#include "Terrain/LaunchPad.h"
#include "Terrain/Lava.h"
#include "Terrain/CheckPoint.h"

#include <fstream>
#include <vector>
#include <string>

enum dir {HORIZONTAL, VERTICAL};
//enum liveness { ALIVE, DEAD };
const int FRAME_NUMBERS = 40;
const int STAGE_NUMBERS = 1;
const int PAD_COUNDOWN = 5;

class Scene
{
private:
	dir state = VERTICAL;
	//liveness life = ALIVE;
	string fileName = "Terrain";
	int stage = 2;
	//--pos
	ofVec2f charaPos = { 100, 500 };
	ofVec2f revivePoint = { 100, 100 };

	//--character declaration
	Chara character = Chara(charaPos);
	
	//--mapping
	vector <FloorLine> floor;
	vector <Ceiling> ceiling;
	vector <Wall> wallLeft;
	vector <Wall> wallRight;

	vector <LaunchPad> pad;
	vector <Platform> box;
	vector <Lava> lava;
	vector <CheckPoint> checkpoint;
	GoalArea goal;

	//--private methods
	void syncButtons();
	void unloadStage();
	vector <FloorLine> findFloor();
	vector <Ceiling> findCeiling();
	vector <Wall> findWallLeft();
	vector <Wall> findWallRight();
	bool toRevivePoint();

	//for arithemics
	float movedpxY = 0;
	float movedpxX = 0;
	int frames = FRAME_NUMBERS;
	bool WinTemp = false;
	float timestamp;
	int coundown = PAD_COUNDOWN;
	bool doCount = false;
	bool is_dead = false;
	bool can_short_jump = true;

public:
	Scene(int stage = 1);
	~Scene();
	bool w_pressed = false, a_pressed = false, s_pressed = false, d_pressed = false;
	bool up_pressed = false, down_pressed = false;
	bool can_move = true;
	bool can_display = false;
	bool loaded = false;
	bool movedCam = false;
	bool fadeOut = false;
	bool fadeIn = true;
	bool is_win = false;

	//for stage loading
	void loadStage(int stage = 1);
	void reloadStage() { loadStage(this->stage); }
	void writeCurrentStageToFile();

	//for stage switching
	void dead(); //Will be put into private

	bool winTest();
	void update();
	void movementUpdate();
	void display();
	void CamUpdate();

};