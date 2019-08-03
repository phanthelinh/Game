#include "DemoScene.h"
#include "SceneManager.h"
#include "TitleScene.h"

DemoScene::DemoScene()
{
	map = new GameMap(16, 16, 128, 30, "Resources/map/Charleston.png", "Resources/map/Charleston.csv");
	currentLevel = 1;
	//init for Player
	PLAYER; //get instance
	PLAYER->posX = 9;
	PLAYER->posY = 384;
	PLAYER->isOnGround = false;
	PLAYER->currentState = new PlayerFallingState();
	CAMERA->camPosition = PLAYER->GetPosition();
	CAMERA->isFollowY = true;
	//implement grid
	GRID;
	LoadGridFromFile(1);

}

DemoScene::~DemoScene()
{
}

void DemoScene::Update(float deltaTime)
{
	auto now = GetTickCount();
	if ((now - timePause) / 1000.0f >= GLOBAL->g_ChangeScene_Delay && isGamePause)
	{

		ReloadResources(currentLevel);
		isGamePause = false;
	}
	if (isGamePause)
		return;
	//object will be move to another cell, that is included in Update Grid
	GRID->UpdateGrid(deltaTime);
	PLAYER->Update(deltaTime);
	PLAYER->HandleKeyboard(keys, deltaTime);
	EXPLODE->Update(deltaTime);

	if (!shieldInserted)
	{
		GRID->AddObject(PLAYER->shield);
		shieldInserted = true;
	}
	CheckForNextStage();
	//
	//COLLISION
	//
	//check collision Ground <> Player
	bool onGround = false;
	bool onWater = false;
	for (auto g : GRID->GetVisibleGround())
	{
		if (g->IsCollide(PLAYER->GetBound()))
		{
			onGround = true;
			auto m = g->IsCollide(PLAYER->GetBound());
			auto b = PLAYER->GetBound();
			break;
		}
	}
	for (auto w : GRID->GetVisibleWater())
	{
		if (COLLISION->IsCollide(w->GetBoundingBox(), PLAYER->GetBoundingBox()))
		{
			onWater = true;
			break;
		}
	}
	if (!onGround && !onWater)
	{
		if (PLAYER->isOnGround)
		{
			PLAYER->ChangeState(Falling);
		}
	}
	//get list colliable objects with player
	auto lstCollideable = GRID->GetColliableObjectsWith(PLAYER, deltaTime);
	//player check collision
	PLAYER->CheckCollision(lstCollideable, deltaTime);
	// visible objects check collision with player
	visibleObject.clear();
	visibleObject = GRID->GetVisibleObjects();
	for (auto obj : visibleObject)
	{
		obj->OnCollision(PLAYER, deltaTime);
		obj->OnCollision(PLAYER->shield, deltaTime);
	}
	if (PLAYER->posX >= 350 && isSpawned == false)
	{
		isSpawned = true;
		RunningMan* runningman3 = new RunningMan(220, 436, 0, 0);
		GRID->AddObject(runningman3);
	}
}

void DemoScene::Draw()
{
	//render map
	map->RenderMap();
	//draw visible objects
	for (auto obj : visibleObject)
	{
		if (obj->tag != Tag::ShieldTag)
			obj->Draw();
	}
	//render player
	PLAYER->Draw();
	EXPLODE->Draw();
}

void DemoScene::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;
	PLAYER->OnKeyDown(keyCode);
}

void DemoScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;
	PLAYER->OnKeyUp(keyCode);
}

void DemoScene::ReleaseAll()
{
	PLAYER->Release();
	if (PLAYER)
	{
		delete PLAYER;
	}
	if (CAMERA)
	{
		delete CAMERA;
	}
	if (COLLISION)
	{
		delete COLLISION;
	}
	if (map != nullptr)
	{
		map->Release();
		delete map;
	}
}

void DemoScene::CheckCollision(BoundingBox player, std::unordered_set<GameObject*> listObj, float deltaTime)
{

}

void DemoScene::CheckForNextStage()
{
	switch (currentLevel)
	{
	case 1://
		if (PLAYER->posX >= GLOBAL->g_Scene1_EndMap)
		{
			currentLevel++;
			ChangingStage();
		}
		break;
		/*case 2:
			map = new GameMap(16, 16, 80, 60, "Resources/map/Pittsburgh_1_1.bmp", "Resources/map/Pittsburgh_1_1.csv");
			break;*/
	case 4:
		break;
	}
}

void DemoScene::ChangingStage()
{
	timePause = GetTickCount();
	isGamePause = true;
}



void DemoScene::ReloadResources(int level)
{
	std::vector<RECT> grounds;
	if (level == 1)
		return;
	switch (level)
	{
	case 2://boss 1
		map = new GameMap(16, 16, 16, 15, "Resources/map/Charleston_boss.png", "Resources/map/Charleston_boss.csv");
		PLAYER->SetPosition(D3DXVECTOR3(16, 168, 0));
		PLAYER->shield = new Shield();
		CAMERA->isFollowY = false;
		wizard = new WizardBoss(240, 52);
		GRID->AddObject(wizard);
		LoadGridFromFile(currentLevel);
		break;
	case 3:
		map = new GameMap(16, 16, 80, 60, "Resources/map/Pittsburgh_1_1.bmp", "Resources/map/Pittsburgh_1_1.csv");
		LoadGridFromFile(currentLevel);
		break;
	case 4:
		break;
	}
}

void DemoScene::SaveGridToFile(int level)
{
	std::ofstream file;
	std::string filename = "Resources/grid/level_" + std::to_string(level) + ".txt";
	file.open(filename);
	for (auto o : GRID->objects)
	{
		//get object info
		switch (o->tag)
		{
		case GroundTag:
		{
			file << "\nground ";
			file << o->posX << " " << o->posY << " " << o->width << " " << o->height;
			break;
		}
		case WaterTag:
		{
			file << "\nwater ";
			file << o->posX << " " << o->posY << " " << o->width << " " << o->height;
			break;
		}
		case EnemyTag:
		{
			auto enemy = (Enemy*)o;
			switch (enemy->enemySubTag)
			{
			case DomestoTag:
			{
				auto domesto = (Domesto*)enemy;
				file << "\ndomesto ";
				file << domesto->posX << " " << domesto->posY << " " << domesto->domestoType;
				break;
			}
			case RunningManTag:
			{
				auto runningman = (RunningMan*)enemy;
				file << "\nrunningman ";
				file << runningman->posX << " " << runningman->posY << " " << runningman->type << " "<<runningman->color;
				break;
			}
			case WizardBossTag:
			{
				auto wizardbo = (WizardBoss*)enemy;
				file << "\nwizard ";
				file << wizardbo->posX << " " << wizardbo->posY;
				break;
			}
			default:
				break;
			}
			break;
		}
		case ItemContainerTag:
		{
			auto item = (ItemsContainer*)o;
			int hasExit = item->hasExit > 0 ? item->hasExit : 0;
			file << "\nitemscontainer ";
			file << item->posX << " " << item->posY << " " << item->width << " " << item->height << " "<<hasExit <<" "<<item->strItems;
			break;
		}
		default:
			break;
		}
	}
	file.close();
}

void DemoScene::LoadGridFromFile(int level)
{
	std::ifstream file;
	std::string filename = "Resources/grid/level_" + std::to_string(level) + ".txt";
	file.open(filename);
	GRID->ResetGrid();
	if (!file.good())
	{
		file.close();
		//add ground from file to cell
		auto grounds = Util::GetAllObjectFromFile(GroundTag, level);
		for (auto g : grounds)
		{
			GameObject* gr = new Ground(g);
			GRID->AddObject(gr);
		}
		////add water from file to cell
		auto data = Util::GetAllObjectFromFile(WaterTag, level);
		for (auto w : data)
		{
			GameObject* water = new Water(w);
			GRID->AddObject(water);
		}
		//load items and container
		ItemsContainer::InsertFromFile(level);
		//add enemy
		//domesto
		Domesto::InsertFromFile(level);
		RunningMan::InsertFromFile(level);
		SaveGridToFile(level);
		return;
	}
	int count = 0;
	while (!file.eof())
	{
		std::string objectname;
		file >> objectname;
		if (objectname._Equal(""))
		{
			break;
		}
		count++;
		if (objectname._Equal("ground"))
		{
			int x,y,w,h;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			GRID->AddObject(new Ground(x, y, w, h));
		}
		else if (objectname._Equal("water"))
		{
			int x, y, w, h;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			GRID->AddObject(new Water(x, y, w, h));
		}
		else if (objectname._Equal("domesto"))
		{
			int x, y, type;
			file >> x;
			file >> y;
			file >> type;
			type == 0 ? GRID->AddObject(new Domesto(x, y, EnemyDomestoType::DomestoRunning)): GRID->AddObject(new Domesto(x, y, EnemyDomestoType::DomestoRunning));
		}
		else if (objectname._Equal("runningman"))
		{
			int x, y, type, color;
			file >> x;
			file >> y;
			file >> type;
			file >> color;
			GRID->AddObject(new RunningMan(x, y, type, color));
		}
		else if (objectname._Equal("wizard"))
		{
			int x, y;
			file >> x;
			file >> y;
			GRID->AddObject(new WizardBoss(x, y));
		}
		else if (objectname._Equal("itemscontainer"))
		{
			int x, y, w, h, hs;
			std::string items;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			file >> hs;
			file >> items;
			GRID->AddObject(new ItemsContainer(x, y, w, h, items, hs));
		}
	}
	file.close();
}
