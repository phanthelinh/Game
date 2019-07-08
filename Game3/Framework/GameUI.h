#pragma once
#include "Sprite.h"
#include "Animation.h"
#include "Font.h"
#include <vector>

using namespace std;

#define MAX_HP 20

class GameUI
{
protected:
	Animation * _sprite;
	Font* _arial;
	int _playerScore;
	int _gameTimer;
	int _gameStage;
	int _weaponCount;
	int _playerHP;
	int _enemyHP;
	int _liveCount;
	int _currentWeapon;
	Animation* weapon;
	int _playerX;
	int _playerY;
	int _viewPortY;
	int _viewPortX;

	Animation* _hpSprite;
	void _initialize();
public:
	GameUI();
	GameUI(int size_, int screenWidth_, int screenHeight_);
	~GameUI();
	void drawTable();
	void drawScore();
	// deltaTime is in second
	void initTimer(int deltaTime_);
	int getTimer(); // return Time left of game in second
	void SetTimer(int x);
	void SetplayerScore(int x);
	// deltaTime_ is in milisecond
	void updateScore(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, int enemyHP_ = 20);

};