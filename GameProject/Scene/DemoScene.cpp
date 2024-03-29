#include "DemoScene.h"
#include "SceneManager.h"
#include "TitleScene.h"

DemoScene::DemoScene()
{
	map = new GameMap(16, 16, 128, 30, "Resources/map/Charleston.png", "Resources/map/Charleston.csv");
	currentLevel = 3;
	//init for Player
	PLAYER; //get instance
	PLAYER->posX = 16;
	PLAYER->posY = 413;
	PLAYER->isOnGround = false;
	PLAYER->currentState = new PlayerStandingState();
	CAMERA->camPosition = PLAYER->GetPosition();
	CAMERA->isFollowY = true;
	//implement grid
	GRID;
	LoadGridFromFile(currentLevel);
	ReloadResources(currentLevel); //test tank
	SOUND->play("soundtrack", true);
	
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
		return;
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
	if (!onGround && !onWater && !PLAYER->isStandOnFlyingBar && PLAYER->currentState->GetState() != OnShield)
	{
		if (PLAYER->isOnGround)
		{
			SOUND->play("jump");
			PLAYER->ChangeState(Falling);
		}
	}

	if (PLAYER->isStandOnFlyingBar && PLAYER->barObject != NULL &&!COLLISION->IsCollide(PLAYER->GetBoundingBox(), PLAYER->barObject->GetBoundingBox()))
	{
		PLAYER->isStandOnFlyingBar = false;
	}
	//update flying bar
	for (auto o : GRID->GetObjectsByTag(FlyingBarTag))
	{
		o->Update(deltaTime);
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
	CheckForNextStage();
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
		if (PLAYER->posX >= GLOBAL->g_Scene1_EndMap && PLAYER->hasExit)
		{
			PLAYER->hasExit = false;
			currentLevel++;
			ChangingStage();
		}
		break;
	case 2:
		if (PLAYER->posX >= GLOBAL->g_Scene2_EndMap && PLAYER->isBossKilled)
		{
			PLAYER->hasExit = false;
			currentLevel++;
			ChangingStage();
		}
		break;
	case 3:
		if (PLAYER->posX >= 944 && PLAYER->posY >= 864 && PLAYER->hasExit)
		{
			PLAYER->hasExit = false;
			currentLevel++;
			ChangingStage();
		}
		break;
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
	if (level == 1)
		return;
	switch (level)
	{
	case 2://boss 1
		map = new GameMap(16, 16, 16, 15, "Resources/map/Charleston_boss.png", "Resources/map/Charleston_boss.csv");
		PLAYER->SetPosition(D3DXVECTOR3(16, 140, 0));
		PLAYER->shield = new Shield();
		CAMERA->isFollowY = false;
		LoadGridFromFile(level);
		break;
	case 3:
		map = new GameMap(16, 16, 64, 60, "Resources/map/Pittsburgh_out.png", "Resources/map/Pittsburgh.csv");
		PLAYER->SetPosition(D3DXVECTOR3(16, 200, 0));
		PLAYER->shield = new Shield();
		CAMERA->isFollowY = true;
		LoadGridFromFile(level);
		break;
	case 4:
		SCENES->ReplaceScene(new Scene4());
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
			case TankTag:
			{
				auto tnk = (Tank*)enemy;
				file << "\ntank ";
				file << tnk->posX << " " << tnk->posY << " " << tnk->initState;
				break;
			}
			case GigiTag:
			{
				auto gigi = (Gigi*)enemy;
				file << "\ngigi ";
				file << gigi->posX << " " << gigi->posY;
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
		case FlyingBarTag:
		{
			auto fb = (FlyingBar*)o;
			file << "\nflyingbar ";
			file << fb->posX << " " << fb->posY << " " << fb->endPoint.x << " " << fb->endPoint.y << " " << fb->type;
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
		Gigi::InsertFromFile(level);
		ItemsContainer::InsertFromFile(level);
		
		//add boss
		WizardBoss::InsertFromFile(level);
		
		//add enemy
		//domesto
		Domesto::InsertFromFile(level);
		RunningMan::InsertFromFile(level);
		Tank::InsertFromFile(level);
		FlyingBar::InsertFromFile(level);
		Gigi::InsertFromFile(level);
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
		else if (objectname._Equal("tank"))
		{
			int x, y, t;
			file >> x;
			file >> y;
			file >> t;
			GRID->AddObject(new Tank(x, y, t));
		}
		else if (objectname._Equal("flyingbar"))
		{
			int st, sy, ex, ey, t;
			file >> st >> sy >> ex >> ey >> t;
			GRID->AddObject(new FlyingBar(st, sy, ex, ey, t));
		}
		else if (objectname._Equal("gigi"))
		{
			int x, y;
			file >> x >> y;
			GRID->AddObject(new Gigi(x, y));
		}
	}
	file.close();
}
