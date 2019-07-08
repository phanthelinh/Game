#include "GameUI.h"

void GameUI::_initialize()
{
	weapon = new Animation("Resources/ui/health_4_6.png", 1, 1, 1);
	_hpSprite = new Animation("Resources/ui/health_4_6.png", 1, 1, 1);
	_gameTimer = 0;
}

GameUI::GameUI()
{
}

GameUI::GameUI(int size_, int screenWidth_, int screenHeight_)
{
	this->_initialize();
	_sprite = new Animation("Resources/ui/blackboard_256_40.png", 1, 1, 1);
	_arial = new Font(GlobalVar::GetDevice(), size_, screenWidth_, screenHeight_);
}

GameUI::~GameUI()
{
}

void GameUI::drawTable()
{
	//// draw table
	_sprite->Draw(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(), RECT(), D3DXVECTOR3(0, 0, 0));
	// draw hp
	for (int i = 0; i<_playerHP; i++)
	{
		_hpSprite->Draw(D3DXVECTOR3(55 + 4 * i, 17, 0), D3DXVECTOR3(), RECT(),D3DXVECTOR3(0,0,0));
	}
	//draw boss
	for (int i = 0; i<_enemyHP; i++)
	{
		_hpSprite->Draw(D3DXVECTOR3(55 + 4 * i, 25, 0), D3DXVECTOR3(), RECT(), D3DXVECTOR3(0, 0, 0));
	}
	//draw weapon
	weapon->Draw(D3DXVECTOR3(130, 18, 0), D3DXVECTOR3(), RECT(), D3DXVECTOR3(0, 0, 0));
}

void GameUI::drawScore()
{
	_arial->onLost();
	_arial->render("SCORE", 2, 8);
	_arial->render(_playerScore, 50, 8);
	_arial->render("TIME", 105, 8);
	_arial->render(_gameTimer / 1000, 145, 8);
	_arial->render("STAGE", 185, 8);
	_arial->render(_gameStage, 232, 8);
	_arial->render("PLAYER", 2, 15);
	_arial->render("ENEMY", 2, 25);
}

void GameUI::initTimer(int deltaTime_)
{
	_gameTimer = deltaTime_ * 1000;
}

int GameUI::getTimer()
{
	return _gameTimer / 1000;
}

void GameUI::SetTimer(int x)
{
	_gameTimer += x;
}

void GameUI::SetplayerScore(int x)
{
	_playerScore += x;
}

void GameUI::updateScore(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, int enemyHP_)
{
	_gameStage = gameStage_;
	_playerScore = playerScore_;
	if (_gameTimer <= 0)
	{
	}
	else
		_gameTimer = _gameTimer - deltaTime_;
	_playerHP = playerHP_;
	_enemyHP = enemyHP_;
	_liveCount = liveCount_;
}