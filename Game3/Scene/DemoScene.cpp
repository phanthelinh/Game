#include "DemoScene.h"
#include<string>
#include <iostream>
#include <exception>
#include <stdlib.h>
#include <time.h>


DemoScene::DemoScene()
{
	LoadContent();
}


DemoScene::~DemoScene()
{
	Memory::SafeDelete(player);
	Memory::SafeDelete(collision);
	keys.clear();
	mapSectionData.clear();
	listObject.clear();
	panthers.clear();
}

void DemoScene::LoadContent()
{
	/*_map = new GameMap(16, 16, 48, 12, "Resources/map/level0_topdown_16_16.bmp", mapdata_l0);*/
	
	player = new Player();
	player->SetPosition(100, 144);

	currentStage = 4;
	ChangingScene(currentStage);

	allowPlayerMove = true;
	opendoor = 2;
	stopmovingcam = onprocessingdoor = false;
	doorObj = NULL;
	gameUI = new GameUI(12, GlobalVar::GetScreenHeight(), GlobalVar::GetScreenHeight());
	gameUI->initTimer(100);
	atBoss = false;

	randomTime = lastTimeExistObj = 0;
	countRandomFishmen = 2;
}

void DemoScene::Update(float deltaTime)
{
	gameUI->updateScore(4, 200, dt, 3, 10);
	if (allowPlayerMove)
	{
		player->HandleKeyboard(keys);
		player->Update(deltaTime);
		//only moving camera if it is not at boss stage
		if(!IsAtBoss(_map->GetCamera()->GetCameraPosition()))
			_map->UpdateMap(player->GetPosition());

		//insert some type of enemy
		GetRandomObject(randomObject);

		QTree = new QuadTree(32, _map->GetCamera()->GetBound());
		for (int i = 0; i < listObject.size(); i++)
		{
			QTree->InsertNode(listObject[i]);
		}

		for (int i = 0; i < randomObject.size(); i++)
		{
			QTree->InsertNode(randomObject[i]);
		}
		for (int i = 0; i < panthers.size(); i++)
			QTree->InsertNode(panthers[i]);

		CollidableList.clear();
		QTree->Retrieve(CollidableList, player);
		//update colliable list
		for (int i = 0; i < CollidableList.size(); i++)
		{
			if (CollidableList.at(i) != NULL &&
				CollidableList.at(i)->Tag != GameObject::Ground &&
				CollidableList.at(i)->Tag != GameObject::NextSection &&
				CollidableList.at(i)->Tag != GameObject::NextStage)
			{
				CollidableList.at(i)->SetPlayerPosition(player->GetPosition());
				CollidableList.at(i)->Update(deltaTime);
				if (CollidableList.at(i)->Tag == GameObject::PhantomBatObj)
					CollidableList.at(i)->isEnable = true;
			}
		}
		//update for weapon exist that enemy was killed in Random
		for (int i = 0; i < randomObject.size(); i++)
		{
			if (randomObject[i]->GetWeaponObject() != NULL)
			{
				randomObject[i]->GetWeaponObject()->Update(deltaTime);
			}
			if (randomObject[i]->GetItems() != NULL)
			{
				randomObject[i]->GetItems()->Update(deltaTime);
			}
		}
		//update for weapon exist that enemy was killed in listObject
		for (int i = 0; i < listObject.size(); i++)
		{
			if (listObject[i]->GetWeaponObject() != NULL)
			{
				listObject[i]->GetWeaponObject()->Update(deltaTime);
			}
			//update for items exist that was in listObject
			if (listObject[i]->GetItems() != NULL)
			{
				listObject[i]->GetItems()->Update(deltaTime);
			}
		}
		

		//check collision
		CheckCollision(this->player->getBox(), CollidableList, deltaTime);
		QTree->Clear();
		delete QTree;
	}
	else //processing for the door
	{
		if (!stopmovingcam)
		{
			//start to move camera
			if (!this->player->GetCurrentReverse()) //go to the right
			{
				_map->GetCamera()->SetCameraPosition(_map->GetCamera()->GetCameraPosition() +
					D3DXVECTOR3(5, 0, 0));
				if (isMoveFist) //move camera first, compare with player
				{
					if (_map->GetCamera()->GetCameraPosition().x > this->player->GetPosition().x) //stop moving camera
					{
						_map->GetCamera()->SetCameraPosition(this->player->GetPosition().x, _map->GetCamera()->GetCameraPosition().y);
						if (opendoor == 2) //first move
						{
							opendoor = 1; //open door
							stopmovingcam = true;
							onprocessingdoor = true;
							isMoveFist = false;
						}
					}
				}
				else
				{
					if (_map->GetCamera()->GetCameraPosition().x > doorObj->getBox().left + _map->GetCamera()->GetCameraWidth() / 2) //stop moving camera
					{
						_map->GetCamera()->SetCameraPosition(doorObj->getBox().left + _map->GetCamera()->GetCameraWidth() / 2, _map->GetCamera()->GetCameraPosition().y);
						if (opendoor == 0)
						{
							_map->NextSection(pos_not_used);//change to the next section
							this->player->SetPosition(targetDest, this->player->GetPosition().y);
							//reset variable
							allowPlayerMove = true;
							opendoor = 2;
							stopmovingcam = onprocessingdoor = false;
							isMoveFist = true;
							//prevent return back
							doorObj->isEnable = false;
							doorObj = nullptr;
						}
					}
				}
				
			}
			else //go to the left
			{
				_map->GetCamera()->SetCameraPosition(_map->GetCamera()->GetCameraPosition() -
					D3DXVECTOR3(5, 0, 0));
				if (isMoveFist) //move camera first, compare with player
				{
					if (_map->GetCamera()->GetCameraPosition().x < this->player->GetPosition().x) //stop moving camera
					{
						_map->GetCamera()->SetCameraPosition(this->player->GetPosition().x, _map->GetCamera()->GetCameraPosition().y);
						if (opendoor == 2) //first move
						{
							opendoor = 1; //open door
							stopmovingcam = true;
							onprocessingdoor = true;
							isMoveFist = false;
						}
					}
				}
				else
				{
					if (_map->GetCamera()->GetCameraPosition().x < doorObj->getBox().right - _map->GetCamera()->GetCameraWidth() / 2) //stop moving camera
					{
						_map->GetCamera()->SetCameraPosition(doorObj->getBox().right - _map->GetCamera()->GetCameraWidth() / 2, 
							_map->GetCamera()->GetCameraPosition().y);
						if (opendoor == 0)
						{
							_map->NextSection(pos_not_used);//change to the next section
							this->player->SetPosition(targetDest, this->player->GetPosition().y);
							//reset variable
							allowPlayerMove = true;
							opendoor = 2;
							stopmovingcam = onprocessingdoor = false;
							isMoveFist = true;
							//prevent return back
							doorObj->isEnable = false;
							doorObj = nullptr;
						}
					}
				}
			}
		}
		else
		{
			this->player->SetState(PlayerState::Running);
			//moving player
			if (this->player->GetCurrentReverse()) //move to the left
			{
				this->player->AddPosition(-5.0f, 0);
				if (this->player->GetPosition().x <= targetDest)
				{
					this->player->SetPosition(targetDest, this->player->GetPosition().y);
					this->player->SetState(PlayerState::Standing);
					opendoor = 0; //close the door
					if (doorObj != NULL)
					{
						doorObj->OpeningTheDoor(opendoor);
					}
					stopmovingcam = false; //allow to move camera second time
				}
				this->player->Update(deltaTime);
			}
			else //move to the right
			{
				this->player->AddPosition(5.0f, 0);
				//this->player->SetPosition(this->player->GetPosition().x + 11.0f, this->player->GetPosition().y);
				if (this->player->GetPosition().x >= targetDest)
				{
					this->player->SetPosition(targetDest, this->player->GetPosition().y);
					this->player->SetState(PlayerState::Standing);
					opendoor = 0;
					if (doorObj != NULL)
					{
						doorObj->OpeningTheDoor(opendoor);
					}
					stopmovingcam = false; //allow to move camera second time
				}
				this->player->Update(deltaTime);
			}
			
		}
		
	}
	
	//set player is not out of screen
	if (player->GetPosition().x < _map->GetCamera()->GetCameraPosition().x - GlobalVar::GetScreenWidth() / 2 + 5) //out in the left side
	{
		player->SetPosition(_map->GetCamera()->GetCameraPosition().x - GlobalVar::GetScreenWidth() / 2 + 5, player->GetPosition().y);
	}
	if (player->GetPosition().x > _map->GetCamera()->GetCameraPosition().x + GlobalVar::GetScreenWidth() / 2 - 5) //out in the right side
	{
		player->SetPosition(_map->GetCamera()->GetCameraPosition().x + GlobalVar::GetScreenWidth() / 2 - 5, player->GetPosition().y);
	}

	
}

void DemoScene::Draw()
{
	_map->RenderMap();
	if (allowPlayerMove)
	{
		for (int i = 0; i < CollidableList.size(); i++)
		{
			CollidableList[i]->Draw(D3DXVECTOR3(), _map->GetCamera()->GetCameraPosition(), RECT(), D3DXVECTOR3(0, 0, 0));
		}
		// random objects check for out screen
		for (int i = 0; i < randomObject.size(); i++)
		{
			if (randomObject[i]->GetPosition().x < _map->GetCamera()->GetCameraPosition().x - GlobalVar::GetScreenWidth() / 2 ||
				randomObject[i]->GetPosition().x > _map->GetCamera()->GetCameraPosition().x + GlobalVar::GetScreenWidth() / 2 ||
				randomObject[i]->GetPosition().y > _map->GetCamera()->GetCameraPosition().y + (GlobalVar::GetScreenHeight() - GlobalVar::GetGameUIArea()) / 2)
			{
				randomObject[i]->isVisible = false;
			}
			//force to draw random object
			randomObject[i]->Draw(D3DXVECTOR3(), _map->GetCamera()->GetCameraPosition(), RECT(), D3DXVECTOR3(0, 0, 0));
			//delete if it out of screen or be killed
			if(!randomObject[i]->isVisible) 
			{
				if(randomObject[i]->GetWeaponObject() == NULL && randomObject[i]->GetItems() == NULL)
				{
					randomObject.erase(randomObject.begin() + i);
				}
				if (randomObject.size() == 0)
					lastTimeExistObj = GetTickCount();
			}
			
		}
		
		for (int i = 0; i < panthers.size(); i++)
		{
			if (panthers[i]->GetPosition().x < _map->GetCamera()->GetCameraPosition().x - GlobalVar::GetScreenWidth() / 2 ||
				panthers[i]->GetPosition().x > _map->GetCamera()->GetCameraPosition().x + GlobalVar::GetScreenWidth() / 2)
			{
				panthers[i]->isVisible = false;
			}
			else
				panthers[i]->isVisible = true;
			if (abs(panthers[i]->GetPosition().x - player->GetPosition().x) < 600)
				panthers[i]->isEnable = true;
			if (panthers[i]->isVisible)
				panthers[i]->Draw(D3DXVECTOR3(), _map->GetCamera()->GetCameraPosition(), RECT(), D3DXVECTOR3(0, 0, 0));
		}
	}
	player->Draw(player->GetPosition(), _map->GetCamera()->GetCameraPosition());
	gameUI->drawTable();
	gameUI->drawScore();
	/*RECT r = { 0,0,200,48 };
	UIDrawing::DrawingText(std::to_string(this->player->GetState()).c_str(), r);*/
}

void DemoScene::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;
	player->OnKeyPressed(keyCode);
	if (keyCode == VK_RETURN)
	{
		ChangingScene(++currentStage);
	}
}

void DemoScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;
	player->OnKeyUp(keyCode);
}

void DemoScene::OnMouseDown(float x, float y)
{
}

void DemoScene::ChangingScene(int stage)
{
	D3DXVECTOR3 new_playerPos = player->GetPosition();
	if (_map!=NULL && !_map->IsEndSection()) //is not end map
	{
		_map->NextSection(new_playerPos);
		player->SetPosition(new_playerPos);
		currentStage--;
		return;
	}
	else //end map
	{

	}
	GameMap::MapSectionData sectionDataL5;
	std::pair<int, GameMap::MapSectionData> pair;
	switch (stage)
	{
	case 4:
		Memory::SafeDelete(_map);
		mapSectionData.clear();
		//add section 1
		sectionDataL5.startX = 0;
		sectionDataL5.startY = 0;
		sectionDataL5.direction = GameMap::RenderMapDirection::LeftToRight;
		sectionDataL5.numTilesWidth = 48;
		sectionDataL5.numTilesHeight = 12;
		sectionDataL5.newPlayerPos = D3DXVECTOR3(48, 144, 0);
		pair = { 1, sectionDataL5 };
		mapSectionData.insert(pair);
		//add section 2
		sectionDataL5.startX = 0;
		sectionDataL5.startY = 192;
		sectionDataL5.direction = GameMap::RenderMapDirection::LeftToRight;
		sectionDataL5.numTilesWidth = 97;
		sectionDataL5.numTilesHeight = 12;
		sectionDataL5.newPlayerPos = D3DXVECTOR3(48, 352, 0);
		pair = { 2, sectionDataL5 };
		mapSectionData.insert(pair);
		//add section 3 , door
		sectionDataL5.startX = 1520;
		sectionDataL5.startY = 192;
		sectionDataL5.direction = GameMap::RenderMapDirection::LeftToRight;
		sectionDataL5.numTilesWidth = 22;
		sectionDataL5.numTilesHeight = 12;
		sectionDataL5.newPlayerPos = D3DXVECTOR3(1648, 256, 0);
		pair = { 3, sectionDataL5 };
		mapSectionData.insert(pair);
		//add section 4 ,water
		sectionDataL5.startX = 1536;
		sectionDataL5.startY = 384;
		sectionDataL5.direction = GameMap::RenderMapDirection::LeftToRight;
		sectionDataL5.numTilesWidth = 32;
		sectionDataL5.numTilesHeight = 12;
		sectionDataL5.newPlayerPos = D3DXVECTOR3(1600, 400, 0);
		pair = { 4, sectionDataL5 };
		mapSectionData.insert(pair);
		//add section 5 
		sectionDataL5.startX = 1792;
		sectionDataL5.startY = 192;
		sectionDataL5.direction = GameMap::RenderMapDirection::LeftToRight;
		sectionDataL5.numTilesWidth = 16;
		sectionDataL5.numTilesHeight = 12;
		sectionDataL5.newPlayerPos = D3DXVECTOR3(1909, 360, 0);
		pair = { 5, sectionDataL5 };
		mapSectionData.insert(pair);
		//add section 6 , dooor
		sectionDataL5.startX = 2032;
		sectionDataL5.startY = 192;
		sectionDataL5.direction = GameMap::RenderMapDirection::LeftToRight;
		sectionDataL5.numTilesWidth = 49;
		sectionDataL5.numTilesHeight = 12;
		sectionDataL5.newPlayerPos = D3DXVECTOR3(2112, 256, 0);
		pair = { 6, sectionDataL5 };
		mapSectionData.insert(pair);
		
		_map = new GameMap(mapSectionData, 16, 16, 176, 36, "Resources/map/level4_topdown_16_16.bmp",
			mapdata_l4, new_playerPos); 
		break;
	case 5: //Dungeon stage, The Death

		Memory::SafeDelete(_map);
		mapSectionData.clear();
		
		//add section 1
		sectionDataL5.startX = 768;
		sectionDataL5.startY = 576;
		sectionDataL5.direction = GameMap::RenderMapDirection::LeftToRight;
		sectionDataL5.numTilesWidth = 32;
		sectionDataL5.numTilesHeight = 12;
		sectionDataL5.newPlayerPos = D3DXVECTOR3(800, 720, 0);
		pair = { 1, sectionDataL5 };
		mapSectionData.insert(pair);
		//add section 2
		sectionDataL5.startX = 768;
		sectionDataL5.startY = 384;
		sectionDataL5.direction = GameMap::RenderMapDirection::LeftToRight;
		sectionDataL5.numTilesWidth = 80;// 96;
		sectionDataL5.numTilesHeight = 12;
		sectionDataL5.newPlayerPos = D3DXVECTOR3(860, 553, 0);
		pair = { 2,sectionDataL5 };
		mapSectionData.insert(pair);
		//add section 2.1 door
		sectionDataL5.startX = 2048;
		sectionDataL5.startY = 384;
		sectionDataL5.direction = GameMap::RenderMapDirection::LeftToRight;
		sectionDataL5.numTilesWidth = 16;
		sectionDataL5.numTilesHeight = 12;
		sectionDataL5.newPlayerPos = D3DXVECTOR3(2112, 530, 0);
		pair = { 3, sectionDataL5 };
		mapSectionData.insert(pair);
		//add section 3
		sectionDataL5.startX = 2304;
		sectionDataL5.startY = 384;
		sectionDataL5.direction = GameMap::RenderMapDirection::RightToLeft;
		sectionDataL5.numTilesWidth = 80;// 112;
		sectionDataL5.numTilesHeight = 12;
		sectionDataL5.newPlayerPos = D3DXVECTOR3(2115, 360, 0);
		pair = { 4, sectionDataL5 };
		mapSectionData.insert(pair);
		//add section 3.1 door
		sectionDataL5.startX = 1024;
		sectionDataL5.startY = 384;
		sectionDataL5.direction = GameMap::RenderMapDirection::RightToLeft;
		sectionDataL5.numTilesWidth = 32;// 112;
		sectionDataL5.numTilesHeight = 12;
		sectionDataL5.newPlayerPos = D3DXVECTOR3(960, 336, 0);
		pair = { 5, sectionDataL5 };
		mapSectionData.insert(pair);
		//add section 4
		sectionDataL5.startX = 1024;
		sectionDataL5.startY = 192;
		sectionDataL5.direction = GameMap::RenderMapDirection::RightToLeft;
		sectionDataL5.numTilesWidth = 63;
		sectionDataL5.numTilesHeight = 12;
		sectionDataL5.newPlayerPos = D3DXVECTOR3(932, 170, 0);
		pair = { 6, sectionDataL5 };
		mapSectionData.insert(pair);

		_map = new GameMap(mapSectionData, 16, 16, 144, 48, "Resources/map/level5_bottomup_16_16.bmp", 
			mapdata_l5, new_playerPos);
		break;
	case 6: //Clock Tower stage, The Dracula
		break;
	default:
		break;
	}
	player->SetPosition(new_playerPos);
	LoadMapObject(currentStage, listObject);
}


void DemoScene::CheckCollision(Box player, std::vector<GameObject*> listObj, float deltaTime)
{
	float collisionTime;
	float normalX, normalY;
	Box broadPhase;
	collision = new GameCollision();
	this->player->onGround = false;
	broadPhase = collision->getBroadPhaseRect(player, deltaTime);
	
	//
	//
	//
	for (int i = 0; i < listObj.size(); i++)
	{
		//
		//CHECK COLLISION BETWEEN RANDOM OBJECT AND GROUND
		//
		for (int randomIndex = 0; randomIndex < randomObject.size(); randomIndex++)
		{
			if (listObj[i]->Tag != GameObject::Ground)
				break;
			//only check with Ground
			randomObject[randomIndex]->OnCollision(listObj[i], deltaTime);
		}
		//
		//CHECK COLLISION FOR PANTHERS
		//
		for (int panIndex = 0; panIndex < panthers.size(); panIndex++)
		{
			if (listObj[i]->Tag != GameObject::Ground)
				break;
			panthers[panIndex]->OnCollision(listObj[i], deltaTime);
		}
		//
		//RANDOM WEAPON OBJECT AND PLAYER
		//
		for (int randomIndex = 0; randomIndex < randomObject.size(); randomIndex++)
		{
			if (randomObject[randomIndex]->GetWeaponObject() != NULL &&
				randomObject[randomIndex]->GetWeaponObject()->isVisible)
			{
				this->player->OnCollision(randomObject[randomIndex]->GetWeaponObject(), deltaTime);
			}
		}
		//
		//COLLISION ITEMS WITH GROUND AND SIMON
		//
		if (listObj[i]->GetItems() != NULL && listObj[i]->GetItems()->isVisible)
		{
			for (int j = 0; j < listObj.size(); j++)
			{
				//items check with ground and simon
				if (listObj[i] != listObj[j] && (listObj[j]->Tag == GameObject::Ground))
				{
					listObj[i]->GetItems()->OnCollision(this->player, deltaTime);
					listObj[i]->GetItems()->OnCollision(listObj[j], deltaTime);
				}
			}
		}
		//
		//COLLISION DETECTION WITH NEXT STAGE, NEXT SECTION AND DOOR
		//
		if(collision->isCollide(broadPhase,listObj[i]->getBox()))
		{
			if((listObj[i]->Tag == GameObject::NextSection || listObj[i]->Tag == GameObject::NextStage) && 
				this->player->GetState() != PlayerState::Jumping)
			{
				ChangingScene(++currentStage);
				break;
			}
			else
			{
				//
				//processing for the door
				//
				if (listObj[i]->Tag == GameObject::DoorObj)
				{
					if (!listObj[i]->isEnable)//already check before
					{
						break;
					}
					if (!onprocessingdoor)
					{
						isMoveFist = true;
						//set to standing state
						this->player->SetState(PlayerState::Standing);
						if (!this->player->GetCurrentReverse()) //to the right
						{
							this->player->SetPosition(listObj[i]->getBox().left, this->player->GetPosition().y);
							targetDest = listObj[i]->getBox().right + 80;
						}
						else
						{
							this->player->SetPosition(listObj[i]->getBox().right, this->player->GetPosition().y);
							targetDest = listObj[i]->getBox().left - 80;
						}
						allowPlayerMove = false;
						doorObj = listObj[i];//get the address of this object i
					}
					//open the door
					listObj[i]->OpeningTheDoor(opendoor);
					break;
				}
			}
		}
		//
		//COLLISION BETWEEN WHIP OF PLAYER AND OTHER OBJECT
		//
		if (this->player->GetWeaponObject() != NULL) //whip != null
		{
			listObj[i]->OnCollision(this->player->GetWeaponObject(), deltaTime); //process at obj not whip
			if (listObj[i]->GetWeaponObject() != NULL && listObj[i]->GetWeaponObject()->isVisible)
			{
				listObj[i]->GetWeaponObject()->OnCollision(this->player->GetWeaponObject(), deltaTime);
			}
		}
		//
		//COLLISION CHECK BETWEEN OBJECT'S WEAPON WITH PLAYER
		//
		if (listObj[i]->GetWeaponObject() != NULL && listObj[i]->GetWeaponObject()->isVisible)
		{
			this->player->OnCollision(listObj[i]->GetWeaponObject(), deltaTime);
		}
		//
		//CHECK COLLISION BETWEEN PLAYER WITH ALL OTHER OBJECTS
		//
		if (listObj[i]->isVisible)
		{
			this->player->OnCollision(listObj[i], deltaTime);
			listObj[i]->OnCollision(this->player, deltaTime);
		}
	}
	//if not found ground --> falling
	if (!this->player->onGround && (this->player->GetState() == PlayerState::Running))
		this->player->SetState(PlayerState::Falling);
	Memory::SafeDelete(collision);
}

void DemoScene::LoadMapObject(int stage, std::vector<GameObject*>& _listObject)
{
	_listObject.clear();
	GameObject * obj = NULL;
	switch (stage)
	{
	case 4:
		GameUtility::GetObjectInforFromFile("Resources/map/level4/level4_ground.txt", _listObject, GameObject::Ground);
		GameUtility::GetObjectInforFromFile("Resources/map/level4/level4_bottomstair.txt", _listObject, GameObject::StairBottomObj, true);
		GameUtility::GetObjectInforFromFile("Resources/map/level4/level4_topstair.txt", _listObject, GameObject::StairTopObj, true);
		GameUtility::GetObjectInforFromFile("Resources/map/level4/level4_wall.txt", _listObject, GameObject::WallObj);
		GameUtility::GetObjectInforFromFile("Resources/door/level4_door.txt", _listObject, GameObject::DoorObj);
		GameUtility::GetObjectInforFromFile("Resources/items/level4_bigcandle.txt", _listObject, GameObject::BigCandleObj);
		GameUtility::GetObjectInforFromFile("Resources/items/level4_candle.txt", _listObject, GameObject::CandleObj);
		//next section
		obj = new StaticObject(688, 112, 16, 32);
		obj->Tag = GameObject::NextSection;
		_listObject.push_back(obj);
		obj = new StaticObject(1600, 359, 16, 16);
		obj->Tag = GameObject::NextSection;
		listObject.push_back(obj);
		obj = new StaticObject(1904, 384, 16, 16);
		obj->Tag = GameObject::NextSection;
		listObject.push_back(obj);

		obj = new Panther(706, 271);
		panthers.push_back(obj);
		obj = new Panther(880, 240);
		panthers.push_back(obj);
		obj = new Panther(944, 272);
		panthers.push_back(obj);

		obj = new PhantomBat(2562, 205);
		listObject.push_back(obj);
		break;
	case 5:
		//load ground
		GameUtility::GetObjectInforFromFile("Resources/map/level5_object_ground.txt", _listObject, GameObject::Ground);
		GameUtility::GetObjectInforFromFile("Resources/map/level5_object_stairtop.txt", _listObject, GameObject::StairTopObj, true);
		GameUtility::GetObjectInforFromFile("Resources/map/level5_object_stairbot.txt", _listObject, GameObject::StairBottomObj, true);
		GameUtility::GetObjectInforFromFile("Resources/map/level5_object_axeknight.txt", _listObject, GameObject::AxeKnightObj);
		GameUtility::GetObjectInforFromFile("Resources/map/level5_object_bonetower.txt", _listObject, GameObject::BoneTowerObj, true);
		GameUtility::GetObjectInforFromFile("Resources/map/level5_object_redskeleton.txt", _listObject, GameObject::RedSkeletonObj);
		GameUtility::GetObjectInforFromFile("Resources/map/level5_object_skeleton.txt", _listObject, GameObject::SkeletonObj);
		GameUtility::GetObjectInforFromFile("Resources/map/level5_object_fleamen.txt", _listObject, GameObject::FleamenObj);
		GameUtility::GetObjectInforFromFile("Resources/door/level5_object_door.txt", _listObject, GameObject::DoorObj);
		GameUtility::GetObjectInforFromFile("Resources/map/level5_object_wall.txt", _listObject, GameObject::WallObj);
		obj = new StaticObject(840, 576, 16, 8);
		obj->Tag = GameObject::NextSection; //to section 2
		_listObject.push_back(obj);
		obj = new StaticObject(2121, 385, 16, 8);
		obj->Tag = GameObject::NextSection; //to section 3
		_listObject.push_back(obj);
		obj = new StaticObject(936, 192, 16, 16);
		obj->Tag = GameObject::NextSection;//to section 4
		_listObject.push_back(obj); 
		break;
	case 6:
		break;
	default:
		break;
	}
}

bool DemoScene::IsAtBoss(D3DXVECTOR3 cameraPosition)
{
	switch (currentStage)
	{
	case 4: 
		if (cameraPosition.x == 2688)
			return true;
		else
			return false;
	case 5:
		if (cameraPosition.x == 144)
			return true;
		else
			return false;
	default:
		return false;
	}
}

void DemoScene::GetRandomObject(std::vector<GameObject*>& _randomObj)
{
	D3DXVECTOR3 camPos = _map->GetCamera()->GetCameraPosition();
	GameObject * obj = NULL;
	float now = GetTickCount();

	switch (currentStage)
	{
	case 4:
		//camera.y = 288 && camera.x (128,480), (1056, 1552), (2160,2464) => ghouls
		if (camPos.y == 288 && ((camPos.x >= 128 && camPos.x <= 480) ||
			(camPos.x >= 1056 && camPos.x <= 1552) ||
			(camPos.x >= 2160 && camPos.x <= 2464)))
		{
			if (!isFullRandom) //max is 3 ghouls
			{
				if ((now - randomTime) / 1000.0f >= 0.5f)
				{
					obj = new Ghouls(camPos.x + GlobalVar::GetScreenWidth() / 2, 320);
					_randomObj.push_back(obj);
					isFullRandom = (_randomObj.size() == 3);
					randomTime = now;
				}
			}
			else //full, but continue to request to random, have to wait
			{
				if ((now - lastTimeExistObj) / 1000.0f >= 3.0f)
				{
					if (_randomObj.size() == 0)
					{
						isFullRandom = false;
					}
				}
			}
		}
		//
		//RANDOM FOR FISHMEN
		//
		if (camPos.y == 480 && (camPos.x >= 1670 && camPos.x <= 1920))
		{
			if (!isFullRandom)
			{
				if ((now - randomTime) / 1000.0f >= 0.5f)
				{
					if (countRandomFishmen % 2 == 0)
					{
						obj = new Fishmen(this->player->GetPosition().x + rand()%20 + 60, 512);
					}
					else
					{
						obj = new Fishmen(this->player->GetPosition().x - rand() % 20 - 60, 512);
					}
					countRandomFishmen--;
					_randomObj.push_back(obj);
					isFullRandom = (_randomObj.size() == 2);
					randomTime = now;
				}
			}
			else
			{
				if ((now - lastTimeExistObj) / 1000.0f >= 3.0f)
				{
					if (_randomObj.size() == 0)
					{
						isFullRandom = false;
						countRandomFishmen = 2;
					}
				}
			}
		}
		//
		//RANDOM FOR BAT
		//
		if (camPos.y == 288 && (camPos.x >= 1648 && camPos.x <= 1744))
		{
			if (!isFullRandom)
			{
				if ((now - randomTime) / 1000.0f >= 0.5f)
				{
					bool _left = !this->player->GetCurrentReverse();
					if (_left)
					{
						obj = new Bat(camPos.x + GlobalVar::GetScreenWidth() / 2, 
							this->player->GetPosition().y - rand()%this->player->GetHeight(), _left);
					}
					else
					{
						obj = new Bat(camPos.x - GlobalVar::GetScreenWidth() / 2,
							this->player->GetPosition().y - rand() % this->player->GetHeight(), _left);
					}
					_randomObj.push_back(obj);
					isFullRandom = (_randomObj.size() == 1);
					randomTime = now;
				}
			}
			else
			{
				if ((now - lastTimeExistObj) / 1000.0f >= 3.0f)
				{
					if (_randomObj.size() == 0)
					{
						isFullRandom = false;
					}
				}
			}
		}
		break;
	default:
		break;
	}
}

void DemoScene::GetPanther(std::vector<GameObject*>& panthers)
{
	GameObject * obj;
	obj = new Panther(700, 272);
	panthers.push_back(obj);
	obj = new Panther(880, 240);
	panthers.push_back(obj);
	obj = new Panther(944, 272);
	panthers.push_back(obj);
}