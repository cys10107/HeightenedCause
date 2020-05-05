#include "Scene.h"
//int plat = 0;
//int currentStage = 1;
//int fps = 0;
//float timestamp = 0;
ifstream fin;
ofstream fout;

Scene::Scene(int stage)
{
	loadStage(stage);
}

Scene::~Scene()
{
}

//Stage Loading functions
void Scene::unloadStage()
{
	this->floor.clear();
	this->ceiling.clear();
	this->wallLeft.clear();
	this->wallRight.clear();

	this->box.clear();
	this->pad.clear();
	this->lava.clear();
	this->checkpoint.clear();

	w_pressed = false, a_pressed = false, s_pressed = false, d_pressed = false;
	up_pressed = false, down_pressed = false;
	can_move = true;
	loaded = false;
	movedCam = false;
	fadeOut = false;
	fadeIn = false;
}

void Scene::loadStage(int stage)
{
	cout << this->loaded << endl;
	if (this->loaded)
		this->unloadStage();
	this->stage = stage;
	this->fileName += to_string(this->stage);
	this->fileName += ".txt";
	cout << "opening file: " << this->fileName << "..." << endl;
	fin.open("LevelMap/" + this->fileName);
	if (fin.is_open())
	{
		float temp;
		int num;
		float tempX, tempY;
		cout << "...file successfully opened, loading..." << endl;
		fin >> temp;
		if (temp == 0)
			this->state = HORIZONTAL;
		else if (temp == 1)
			this->state = VERTICAL;
		cout << "...map direction loaded..." << endl;

		fin >> tempX >> tempY;
		//cout << tempX << " " << tempY;
		this->charaPos = { tempX, tempY };
		this->character = Chara(this->charaPos);
		this->revivePoint = { tempX, tempY };
		cout << "...character position loaded..." << endl;
		
		this->floor.clear();
		fin >> num;
		for (int i = 0; i < num; i++)
		{
			float inx1, inx2, iny;
			fin >> inx1 >> inx2 >> iny;
			this->floor.push_back(FloorLine(inx1, inx2, iny));
		}
		if (fin.good())
			cout << "..." << num << " base floors loaded..." << endl;
		else
			cout << "...failed loading base floors..." << endl;

		//fin.get();
		this->ceiling.clear();
		fin >> num;
		for (int i = 0; i < num; i++)
		{
			//cout << "HELLO" << endl;
			float inx1, inx2, iny;
			fin >> inx1;
			fin >> inx2;
			fin >> iny;
			this->ceiling.push_back(Ceiling(inx1, inx2, iny));
		}
		if (fin.good())
			cout << "..." << num << " base ceilings loaded..." << endl;
		else
			cout << "...failed loading base ceilings..." << endl;

		this->wallLeft.clear();
		fin >> num;
		for (int i = 0; i < num; i++)
		{
			//cout << "in" << endl;
			float iny1, iny2, inx;
			fin >> iny1 >> iny2 >> inx;
			this->wallLeft.push_back(Wall(iny1, iny2, inx, LEFT));
		}
		if (fin.good())
			cout << "..." << num << " wallLefts loaded..." << endl;
		else
			cout << "...failed loading wallLefts..." << endl;
	
		this->wallRight.clear();
		fin >> num;
		for (int i = 0; i < num; i++)
		{
			float iny1, iny2, inx;
			fin >> iny1 >> iny2 >> inx;
			this->wallRight.push_back(Wall(iny1, iny2, inx, RIGHT));
		}
		if (fin.good())
			cout << "..." << num << " wallRight loaded..." << endl;
		else
			cout << "...failed loading wallRights..." << endl;

		//this->box.clear();
		fin >> num;
		for (int i = 0; i < num; i++)
		{
			this->box.push_back(Platform());
			this->box[i].fileInput(fin);
		}
		//fin.clear();
		if (fin.good())
			cout << "..." << num << " platformes loaded..." << endl;
		else
			cout << "...failed loading platforms..." << endl;

		fin >> num;
		for (int i = 0; i < num; i++)
		{
			float inX, inY, inLF;
			fin >> inX >> inY >> inLF;
			this->pad.push_back(LaunchPad(inX, inY, inLF));
			//cout << i << endl;
		}
		if (fin.good())
			cout << "..." << num << " launch pads loaded..." << endl;
		else
			cout << "...failed loading launch pads..." << endl;

		fin >> num;
		for (int i = 0; i < num; i++)
		{
			float inX, inY, inW, inH;
			fin >> inX >> inY >> inW >> inH;
			this->lava.push_back(Lava(ofVec2f(inX, inY), inW, inH));
		}
		if (fin.good())
			cout << "..." << num << " lava pits loaded..." << endl;
		else
			cout << "...failed loading lava pits..." << endl;

		fin >> num;
		for (int i = 0; i < num; i++)
		{
			float inX, inY;
			fin >> inX >> inY;
			this->checkpoint.push_back(CheckPoint(ofVec2f(inX, inY)));
		}
		if (fin.good())
			cout << "..." << num << " checkpoints loaded..." << endl;
		else
			cout << "...failed loading checkpoints..." << endl;

		fin >> num;
		if (num == 1)
		{
			float inX, inY, inW, inH;
			fin >> inX >> inY >> inW >> inH;
			this->goal = GoalArea(ofVec2f(inX, inY), inW, inH);
			cout << "...goal loaded..." << endl;
		}
		else
		{
			this->goal = GoalArea(false);
		}

		cout << "...Finished..." << endl;
		this->loaded = true;
		fin.close();
	}
	else
		cout << "couldn't open file, failed..." << endl;
	this->fileName = "Terrain";

	//this->timestamp = ofGetElapsedTimef();
}

void Scene::writeCurrentStageToFile()
{
	int num;
	cout << "...Outputing to file..." << endl;
	this->fileName += to_string(this->stage);
	this->fileName += ".txt";
	fout.open("LevelMap/" + this->fileName);

	//map direction
	fout << this->state << endl;

	//charaPos \n
	fout << this->charaPos.x << " " << this->charaPos.y << endl << endl;
	//floor
	//floor \n
	num = this->floor.size();
	fout << num << endl;
	for (int i = 0; i < num; i++)
	{
		fout << floor[i].getPosA().x << ' '
			<< floor[i].getPosB().x << ' '
			<< floor[i].getPosB().y << endl;
	}
	fout << endl;

	//ceiling
	num = this->ceiling.size();
	fout << num << endl;
	for (int i = 0; i < num; i++)
	{
		fout << ceiling[i].getPosA().x << ' '
			<< ceiling[i].getPosB().x << ' '
			<< ceiling[i].getPosB().y << endl;
	}
	fout << endl;
	//wallLeft
	num = this->wallLeft.size();
	fout << num << endl;
	for (int i = 0; i < num; i++)
	{
		fout << wallLeft[i].getPosA().y << ' '
			<< wallLeft[i].getPosB().y << ' '
			<< wallLeft[i].getPosA().x << endl;
	}
	fout << endl;
	//wallRight
	num = this->wallRight.size();
	fout << num << endl;
	for (int i = 0; i < num; i++)
	{
		fout << wallRight[i].getPosA().y << ' '
			<< wallRight[i].getPosB().y << ' '
			<< wallRight[i].getPosA().x << endl;
	}
	fout << endl;
	//Platform
	num = this->box.size();
	fout << num << endl;
	for (int i = 0; i < num; i++)
	{
		this->box[i].fileOutput(fout);
	}
	fout << endl;
	//launchpads
	num = this->pad.size();
	fout << num << endl;
	for (int i = 0; i < num; i++)
	{
		this->pad[i].fileOutput(fout);
	}
	fout << endl;
	//lavaPits
	if (!this->lava.empty())
	{
		num = this->lava.size();
		fout << num << endl;
		for (int i = 0; i < num; i++)
		{
			this->lava[i].fileOutput(fout);
		}
	}
	else
		fout << 0 << endl;
	fout << endl;
	//checkpoints
	if (!this->checkpoint.empty())
	{
		num = this->checkpoint.size();
		fout << num << endl;
		for (int i = 0; i < num; i++)
		{
			this->checkpoint[i].fileOutput(fout);
		}
	}
	else 
		fout << 0 << endl;
	fout << endl;

	//Goal
	if (this->goal.exsist())
	{
		fout << '1' << endl;
		this->goal.output(fout);
	}
	else
		fout << '0' << endl;
	fout << endl;

	cout << "...finished..." << endl;
	this->fileName = "Terrain";
	fout.close();
}

void Scene::syncButtons()
{
	this->character.a_pressed = this->a_pressed;
	this->character.w_pressed = this->w_pressed;
	this->character.s_pressed = this->s_pressed;
	this->character.d_pressed = this->d_pressed;
	this->goal.w_pressed = this->w_pressed;
}

//Find functions
vector <FloorLine> Scene::findFloor()
{
	vector <FloorLine> temp;
	if (!this->floor.empty())
	{
		temp.push_back(this->floor[0]);

		for (int i = 1; i < this->floor.size(); i++)
		{
			if (this->character.getBLPos().y < this->floor[i].getHeight())
			{
				if (this->floor[i].getHeight() == temp[0].getHeight())
				{
					temp.push_back(this->floor[i]);
					continue;
				}
				if (this->floor[i].getHeight() < temp[0].getHeight())
				{
					//temp.clear();
					temp.push_back(this->floor[i]);
					continue;
				}
			}
			if (this->character.getBRPos().y < this->floor[i].getHeight())
			{
				if (this->floor[i].getHeight() == temp[0].getHeight())
				{
					temp.push_back(this->floor[i]);
					continue;
				}
				if (this->floor[i].getHeight() < temp[0].getHeight())
				{
					//temp.clear();
					temp.push_back(this->floor[i]);
					continue;
				}
			}
		}

		// for boxes
		for (int i = 0; i < this->box.size(); i++)
		{
			if (this->character.getBLPos().y < this->box[i].floor.getHeight())
			{
				if (this->box[i].floor.getHeight() == temp[0].getHeight())
				{
					temp.push_back(this->box[i].floor);
					continue;
				}
				if (this->box[i].floor.getHeight() < temp[0].getHeight())
				{
					//temp.clear();
					temp.push_back(this->box[i].floor);
					continue;
				}
			}
			if (this->character.getBRPos().y < this->box[i].floor.getHeight())
			{
				if (this->box[i].floor.getHeight() == temp[0].getHeight())
				{
					temp.push_back(this->box[i].floor);
					continue;
				}
				if (this->box[i].floor.getHeight() < temp[0].getHeight())
				{
					//temp.clear();
					temp.push_back(this->box[i].floor);
					continue;
				}
			}
		}
	}
	if (temp.empty())
	{
		temp.push_back(this->floor[0]);
	}
	return temp;
}

vector <Ceiling> Scene::findCeiling()
{
	vector <Ceiling> temp;
	temp.push_back(Ceiling(0, 1024, -15000));
	bool changed = false;
	//cout << temp[0].getHeight();
	for (int i = 0; i < this->ceiling.size(); i++)
	{
		if (this->character.getTLPos().y > this->ceiling[i].getHeight() - 1)
		{
			if (this->ceiling[i].getHeight() == temp[0].getHeight())
			{
				changed = true;
				temp.push_back(this->ceiling[i]);
				//continue;
			}
			if (this->ceiling[i].getHeight() > temp[0].getHeight())
			{
				//temp.clear();
				changed = true;
				temp.push_back(this->ceiling[i]);
				//continue;
			}
		}
		if (this->character.getTRPos().y > this->ceiling[i].getHeight() - 1)
		{
			if (this->ceiling[i].getHeight() == temp[0].getHeight())
			{
				temp.push_back(this->ceiling[i]);
				changed = true;
				//continue;
			}
			if (this->ceiling[i].getHeight() > temp[0].getHeight())
			{
				//temp.clear();
				temp.push_back(this->ceiling[i]);
				changed = true;
				//continue;
			}
		}
	}
	//for boxes
	for (int i = 0; i < this->box.size(); i++)
	{
		if (this->character.getTLPos().y > this->box[i].ceiling.getHeight() - 1)
		{
			if (this->box[i].ceiling.getHeight() == temp[0].getHeight())
			{
				temp.push_back(this->box[i].ceiling);
				changed = true;
				//continue;
			}
			if (this->box[i].ceiling.getHeight() > temp[0].getHeight())
			{
				//temp.clear();
				temp.push_back(this->box[i].ceiling);
				changed = true;
				//continue;
			}
		}
		if (this->character.getTRPos().y > this->box[i].ceiling.getHeight() - 1)
		{
			if (this->box[i].ceiling.getHeight() == temp[0].getHeight())
			{
				temp.push_back(this->box[i].ceiling);
				changed = true;
				//continue;
			}
			if (this->box[i].ceiling.getHeight() > temp[0].getHeight())
			{
				//temp.clear();
				temp.push_back(this->box[i].ceiling);
				changed = true;
				//continue;
			}
		}
	}
	if (!changed)
	{
		temp.clear();
	}
	return temp;
}

vector <Wall> Scene::findWallLeft()
{
	vector <Wall> temp;
	temp.push_back(this->wallLeft[0]);
	
	for (int i = 0; i < this->wallLeft.size(); i++)
	{
		if (this->character.getTRPos().x < this->wallLeft[i].getX())
		{
			if (this->wallLeft[i].getX() == temp[0].getX())
			{
				temp.push_back(this->wallLeft[i]);
				//continue;
			}
			if (this->wallLeft[i].getX() < temp[0].getX())
			{
				//temp.clear();
				temp.push_back(this->wallLeft[i]);
				//continue;
			}
		}
	}
	
	//for boxes
	for (int i = 0; i < this->box.size(); i++)
	{
		if (this->character.getTRPos().x < this->box[i].wallLeft.getX())
		{
			if (this->box[i].wallLeft.getX() == temp[0].getX())
			{
				temp.push_back(this->box[i].wallLeft);
				//continue;
			}
			if (this->box[i].wallLeft.getX() < temp[0].getX())
			{
				//temp.clear();
				temp.push_back(this->box[i].wallLeft);
				//continue;
			}
		}
	}
	/*
	if (temp[0].getX() == 10000)
	{
		temp.clear();
	}
	*/
	return temp;
}

vector <Wall> Scene::findWallRight()
{
	vector <Wall> temp;
	temp.push_back(this->wallRight[0]);
	
	for (int i = 0; i < this->wallRight.size(); i++)
	{
		if (this->character.getTLPos().x > this->wallRight[i].getX())
		{
			//cout << this->wallRight[i].getX() << endl;
			if (this->wallRight[i].getX() == temp[0].getX())
			{
				temp.push_back(this->wallRight[i]);
				//continue;
			}
			if (this->wallRight[i].getX() > temp[0].getX())
			{
				//temp.clear();
				temp.push_back(this->wallRight[i]);
				//continue;
			}
		}
	}
	
	//for boxes
	for (int i = 0; i < this->box.size(); i++)
	{
		if (this->character.getTLPos().x > this->box[i].wallRight.getX())
		{
			//cout << this->wallRight[i].getX() << endl;
			if (this->box[i].wallRight.getX() == temp[0].getX())
			{
				temp.push_back(this->box[i].wallRight);
				//continue;
			}
			if (this->box[i].wallRight.getX() > temp[0].getX())
			{
				//temp.clear();
				temp.push_back(this->box[i].wallRight);
				//continue;
			}
		}
	}
	/*
	if (temp[0].getX() == 0)
	{
		temp.clear();
	}
	*/
	return temp;
}

bool Scene::toRevivePoint()
{
	this->character.setX(this->revivePoint.x);
	this->character.setY(this->revivePoint.y);
	return true;
}

void Scene::dead()
{
	//cout << "DEAD" << endl;
	if (!this->is_dead)
	{
		this->is_dead = true;
		this->can_move = false;
		this->fadeOut = true;
		this->character.setVX(0);
	}
}

void Scene::display()
{
	if (this->can_display)
	{
		for (int i = 0; i < this->box.size(); i++)
			this->box[i].display();
		for (int i = 0; i < this->floor.size(); i++)
			this->floor[i].display();

		for (int i = 0; i < this->ceiling.size(); i++)
			this->ceiling[i].display();
		for (int i = 0; i < this->wallLeft.size(); i++)
			this->wallLeft[i].display();
		for (int i = 0; i < this->wallRight.size(); i++)
			this->wallRight[i].display();
		for (int i = 0; i < this->pad.size(); i++)
			this->pad[i].display();
		for (int i = 0; i < this->lava.size(); i++)
			this->lava[i].display();
		for (int i = 0; i < this->checkpoint.size(); i++)
			this->checkpoint[i].display();
		if (this->loaded)
		{
			this->character.display();
			this->goal.display();
		}
	}
	else
	{
		ofSetColor(0, 0, 0);
		ofDrawRectangle(-100, -100, 1500, 1000);
	}

	//Fadein & fadeouts
	if (this->fadeOut == true)
	{
		if (this->frames > 0)
		{
			ofSetColor(0, 0, 0, 255 - (255 / FRAME_NUMBERS) * this->frames);
			ofDrawRectangle(-100, -100, 1500, 1000);
			ofSetColor(255, 255, 255);
			this->frames--;
			if (this->frames == 0)
			{
				this->can_display = false;
			}
		}
		else
		{
			this->frames = FRAME_NUMBERS;
			if (this->stage != STAGE_NUMBERS && !this->is_dead)
			{
				this->fadeOut = false;
				if (this->goal.WinTest(this->character.getBLPos()) || this->goal.WinTest(this->character.getBRPos()))
					this->is_win = true;
			}
			else if (this->is_dead)
			{
				this->is_dead = false;
				this->fadeOut = false;
				this->can_move = true;
				this->toRevivePoint();
				this->movedpxX = this->movedpxY = 0;
				this->fadeIn = true;
			}
		}
	}
	if (this->fadeIn == true)
	{
		if (this->frames > 0)
		{
			this->can_display = true;
			ofSetColor(0, 0, 0, (255 / FRAME_NUMBERS) * this->frames);
			ofDrawRectangle(-100, -100, 1500, 1000);
			ofSetColor(255, 255, 255);
			this->frames--;
		}
		else
		{
			this->frames = FRAME_NUMBERS;
			this->fadeIn = false;
		}
	}
}

bool Scene::winTest()
{
	syncButtons();
	if (this->goal.exsist())
	{
		if (this->is_win == true)
		{
			cout << "win" << endl;
			return true;
		}
		if (this->goal.WinTest(this->character.getBLPos()) || this->goal.WinTest(this->character.getBRPos()))
		{
			this->character.can_jump = false;
			if (this->w_pressed && !this->WinTemp)
			{
				//cout << "win" << endl;
				//this->can_move = false;
				this->fadeOut = true;
			}
			else
				return false;
		}
		this->WinTemp = false;
		return false;
	}
}

void Scene::update()
{

	//LauchPad
	{
		if (!this->pad.empty())
		{
			int size = this->pad.size();
			for (int i = 0; i < size; i++)
			{
				if (this->pad[i].detect(this->character.getBLPos()) || this->pad[i].detect(this->character.getBRPos()))
				{
					this->character.setVY(1);
					//this->character.jumped = true;
					//this->character.setVY(-this->pad[i]._leapForce);
					this->doCount = true;
				}
				if (this->character.jumped && this->doCount && this->coundown > 0)
				{
					this->character.setVY(-this->pad[i]._leapForce);
					this->coundown -= 1;
					this->can_short_jump = false;
				}
				else
				{
					if (this->character.on_floor)
						this->can_short_jump = true;
					this->coundown = PAD_COUNDOWN;
					this->doCount = false;
				}
			}
		}
	}

	//Lava
	{
		if (!this->lava.empty())
		{
			int size = this->lava.size();
			for (int i = 0; i < size; i++)
			{
				if (this->lava[i].detect(this->character.getBLPos()) || this->lava[i].detect(this->character.getBRPos()))
					this->dead();
			}
		}
	}

	//checkpoint
	{
		if (!this->checkpoint.empty())
		{
			int size = this->checkpoint.size();
			for (int i = 0; i < size; i++)
			{
				if (this->checkpoint[i].detect(this->character.getBLPos()) || this->checkpoint[i].detect(this->character.getBRPos()) || this->checkpoint[i].detect(this->character.getTLPos()) || this->checkpoint[i].detect(this->character.getTRPos()))
				{
					this->revivePoint = this->checkpoint[i].getPos();
					this->revivePoint.x += (CHECKPOINT_WIDTH - CHARACTER_WIDTH) / 2;
				}
			}
		}
	}

	//move cam
	//cam movements (sorry it has to go here)
	//up & down
	if (this->state == VERTICAL)
	{
		//cout << "VERTICAL" << endl;
		if (this->character.getRelativeY() < 311)
		{
			this->movedpxY = 312 - this->character.getRelativeY();
			this->movedCam = true;
		}
		else if (this->movedCam && this->character.getRelativeY() >= 561)
		{
			this->movedpxY = -(this->character.getRelativeY() - 561.1);
		}
		else
			this->movedpxY = 0;
	}

	if (this->character.on_floor)
	{
		//this->px = 0;
		this->character.resetVY();
	}
	//left & right
	if (this->state == HORIZONTAL)
	{
		//cout << "HORIZONTAL" << endl;
		if (this->character.getRelativeX() >= 512)
		{
			this->movedpxX = -(this->character.getRelativeX() - 512);
			this->movedCam = true;
		}
		else if (this->movedCam && this->character.getRelativeX() < 312)
		{
			this->movedpxX = 312 - this->character.getRelativeX();
		}
		else
			this->movedpxX = 0;
	}
}

void Scene::movementUpdate()
{
	syncButtons();
	//character update
	//---character key reactions
	this->character.keyReactions(this->can_short_jump);

	//---find the referencing temps before shifting position
	vector <FloorLine>& tempFloor = this->findFloor();
	//vector <int> intVec;
	//intVec.push_back();
	//intVec.clear();
	//for (int i = 0; i < intVec.size(); i++)
	vector <Ceiling>& tempCeiling = this->findCeiling();
	vector <Wall>& tempWallLeft = this->findWallLeft();
	vector <Wall>& tempWallRight = this->findWallRight();
	
	//---process character movements
	if (this->can_move)
		this->character.processMovements();

	//---test if can't stand up
	for (int i = 0; i < tempCeiling.size(); i++)
	{
		ofVec2f TMPos = { (this->character.getTLPos().x + this->character.getTRPos().x) / 2, this->character.getTLPos().y };
		if ((tempCeiling[i].getDistance(this->character.getTLPos()) != 0 && tempCeiling[i].getDistance(this->character.getTLPos()) < (CHARACTER_HEIGHT - CROUCH_HEIGHT) + 2) || 
			(tempCeiling[i].getDistance(this->character.getTRPos()) != 0 && tempCeiling[i].getDistance(this->character.getTRPos()) < (CHARACTER_HEIGHT - CROUCH_HEIGHT) + 2) ||
			(tempCeiling[i].getDistance(TMPos) != 0 && tempCeiling[i].getDistance(TMPos) < (CHARACTER_HEIGHT - CROUCH_HEIGHT) + 2))
		{
			//cout << i << " activated" << endl;
			this->character.is_ceiling_top = true;
			break;
		}
		else
		{
			//cout << 0 << endl;
			this->character.is_ceiling_top = false;
		}
	}
	//cout << this->character.is_ceiling_top << endl;
	
	//---character detections and position limiting
	//floor
	if (!tempFloor.empty())
	{
		bool switch1 = false;	//for floor detection
		int size = tempFloor.size();
		ofVec2f bCenter = { (this->character.getBLPos().x + this->character.getBRPos().x) / 2, this->character.getBLPos().y };
		for (int i = 0; i < size; i++)
		{
			if (tempFloor[i].detect(this->character.getBRPos()) || tempFloor[i].detect(this->character.getBLPos()) || tempFloor[i].detect(bCenter))
			{
				//this->character.resetVY();
				//this->character.setAY(0);
				this->character.setY(tempFloor[i].getHeight() - 1);
				this->character.on_floor = true;
				switch1 = true;
			}
			if (!switch1)
			{
				this->character.on_floor = false;
				this->character.resetAY();
			}
		}
	}
	
	//Ceiling
	{
		if (!tempCeiling.empty())
		{
			//cout << tempCeiling[0].getHeight() << endl;
			int size = tempCeiling.size();
			if (this->character.jumped)
			{
				ofVec2f TMPos = { (this->character.getTLPos().x + this->character.getTRPos().x) / 2, this->character.getTLPos().y };
				for (int i = 0; i < size; i++)
				{
					if (tempCeiling[i].detect(this->character.getTRPos()) || tempCeiling[i].detect(this->character.getTLPos()) || tempCeiling[i].detect(TMPos))
					{
						//cout << "head" << endl;
						this->character.resetVY();
						this->character.setY(tempCeiling[i].getHeight() + (this->character.getBLPos().y - this->character.getTLPos().y) + 1);
						this->character.jumped = false;
					}
				}
			}
		}
	}
	//WallLeft
	{
		if (!tempWallLeft.empty())
		{
			//cout << tempWallLeft[0].getX() << endl;
			int size = tempWallLeft.size();
			ofVec2f midPoint = { this->character.getBRPos().x, (this->character.getTRPos().y + this->character.getBRPos().y) / 2 };
			ofVec2f quarterPoint1 = { midPoint.x, (this->character.getTRPos().y + midPoint.y) / 2 };
			ofVec2f quarterPoint2 = { midPoint.x, (this->character.getBRPos().y + midPoint.y) / 2 };

			for (int i = 0; i < size; i++)
			{
				//control on_wall_left
				if (tempWallLeft[i].detect(midPoint) || tempWallLeft[i].detect(this->character.getBRPos()) || tempWallLeft[i].detect(quarterPoint2))
					this->character.on_wall_left = true;
				else
					this->character.on_wall_left = false;
				//limiting position
				if (tempWallLeft[i].detect(this->character.getTRPos()) || tempWallLeft[i].detect(midPoint) || tempWallLeft[i].detect(this->character.getBRPos()) || tempWallLeft[i].detect(quarterPoint1) || tempWallLeft[i].detect(quarterPoint2))
				{
					this->character.setVX(0);
					this->character.setX(tempWallLeft[i].getX() - CHARACTER_WIDTH - 1);

				}
			}
		}
	}

	//WallRight
	{
		if (!tempWallRight.empty())
		{
			int size = tempWallRight.size();
			ofVec2f midPoint = { this->character.getBLPos().x, (this->character.getTLPos().y + this->character.getBLPos().y) / 2 };
			ofVec2f quarterPoint1 = { midPoint.x, (this->character.getTLPos().y + midPoint.y) / 2 };
			ofVec2f quarterPoint2 = { midPoint.x, (this->character.getBLPos().y + midPoint.y) / 2 };

			for (int i = 0; i < size; i++)
			{
				//control on_wall_right
				if (!this->character.on_floor && (tempWallRight[i].detect(midPoint) || tempWallRight[i].detect(quarterPoint2) || tempWallRight[i].detect(this->character.getBLPos())))
					this->character.on_wall_right = true;
				else
					this->character.on_wall_right = false;

				if (tempWallRight[i].detect(this->character.getTLPos()) || tempWallRight[i].detect(quarterPoint1) || tempWallRight[i].detect(midPoint) || tempWallRight[i].detect(quarterPoint2) || tempWallRight[i].detect(this->character.getBLPos()))
				{
					this->character.setVX(0);
					this->character.setX(tempWallRight[i].getX() + 1.1);
				}
			}
		}
	}

	cout << "character pos: " << this->character.getBLPos().x << ", " << this->character.getBLPos().y << endl;
}

void Scene::CamUpdate()
{
	//for up & down
	if (this->movedpxY != 0)
	{
		for (int i = 0; i < this->box.size(); i++)
		{
			this->box[i].camMove(0, this->movedpxY);
		}
		//for seperated ones
		for (int i = 0; i < this->floor.size(); i++)
		{
			this->floor[i].camMove(0, this->movedpxY);
		}
		for (int i = 0; i < this->ceiling.size(); i++)
		{
			this->ceiling[i].camMove(0, this->movedpxY);
		}
		for (int i = 0; i < this->wallLeft.size(); i++)
		{
			this->wallLeft[i].camMove(0, this->movedpxY);
		}
		for (int i = 0; i < this->wallRight.size(); i++)
		{
			this->wallRight[i].camMove(0, this->movedpxY);
		}
		for (int i = 0; i < this->pad.size(); i++)
		{
			this->pad[i].camMove(0, this->movedpxY);
		}
		for (int i = 0; i < this->lava.size(); i++)
		{
			this->lava[i].camMove(0, this->movedpxY);
		}
		for (int i = 0; i < this->checkpoint.size(); i++)
		{
			this->checkpoint[i].camMove(0, this->movedpxY);
		}
		this->character.camMove(0, this->movedpxY);
		this->goal.camMove(0, this->movedpxY);
	}
	//for left & right
	if (this->movedpxX != 0)
	{
		for (int i = 0; i < this->box.size(); i++)
		{
			this->box[i].camMove(this->movedpxX, 0);
		}
		//for seperated ones
		for (int i = 0; i < this->floor.size(); i++)
		{
			this->floor[i].camMove(this->movedpxX, 0);
		}
		for (int i = 0; i < this->ceiling.size(); i++)
		{
			this->ceiling[i].camMove(this->movedpxX, 0);
		}
		for (int i = 0; i < this->wallLeft.size(); i++)
		{
			this->wallLeft[i].camMove(this->movedpxX, 0);
		}
		for (int i = 0; i < this->wallRight.size(); i++)
		{
			this->wallRight[i].camMove(this->movedpxX, 0);
		}
		for (int i = 0; i < this->pad.size(); i++)
		{
			this->pad[i].camMove(this->movedpxX, 0);
		}
		for (int i = 0; i < this->lava.size(); i++)
		{
			this->lava[i].camMove(this->movedpxX, 0);
		}
		for (int i = 0; i < this->checkpoint.size(); i++)
		{
			this->checkpoint[i].camMove(this->movedpxX, 0);
		}
		this->character.camMove(this->movedpxX, 0);
		this->goal.camMove(this->movedpxX, 0);
	}

	//for keys
	if (this->up_pressed)
	{
		//for boxes
		for (int i = 0; i < this->box.size(); i++)
		{
			this->box[i].camMove(0, 2);
		}
		//for seperated ones
		for (int i = 0; i < this->floor.size(); i++)
		{
			this->floor[i].camMove(0, 2);
		}
		for (int i = 0; i < this->ceiling.size(); i++)
		{
			this->ceiling[i].camMove(0, 2);
		}
		for (int i = 0; i < this->wallLeft.size(); i++)
		{
			this->wallLeft[i].camMove(0, 2);
		}
		for (int i = 0; i < this->wallRight.size(); i++)
		{
			this->wallRight[i].camMove(0, 2);
		}
		for (int i = 0; i < this->pad.size(); i++)
		{
			this->pad[i].camMove(0, 2);
		}
		for (int i = 0; i < this->lava.size(); i++)
		{
			this->lava[i].camMove(0, 2);
		}
		for (int i = 0; i < this->checkpoint.size(); i++)
		{
			this->checkpoint[i].camMove(0, 2);
		}
		this->character.camMove(0, 2);
		this->goal.camMove(0, 2);
	}
	if (this->down_pressed)
	{
		//for boxes
		for (int i = 0; i < this->box.size(); i++)
		{
			this->box[i].camMove(0, -2);
		}
		//for seperated ones
		for (int i = 0; i < this->floor.size(); i++)
		{
			this->floor[i].camMove(0, -2);
		}
		for (int i = 0; i < this->ceiling.size(); i++)
		{
			this->ceiling[i].camMove(0, -2);
		}
		for (int i = 0; i < this->wallLeft.size(); i++)
		{
			this->wallLeft[i].camMove(0, -2);
		}
		for (int i = 0; i < this->wallRight.size(); i++)
		{
			this->wallRight[i].camMove(0, -2);
		}
		for (int i = 0; i < this->pad.size(); i++)
		{
			this->pad[i].camMove(0, -2);
		}
		for (int i = 0; i < this->lava.size(); i++)
		{
			this->lava[i].camMove(0, -2);
		}
		for (int i = 0; i < this->checkpoint.size(); i++)
		{
			this->checkpoint[i].camMove(0, -2);
		}
		this->character.camMove(0, -2);
		this->goal.camMove(0, -2);
	}
}