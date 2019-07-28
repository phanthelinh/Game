#include "PlayerDiedState.h"

PlayeDiedState::PlayeDiedState()
{
	PLAYER->allow[Running] = false;
	PLAYER->allow[Jumping] = false;
	PLAYER->allow[Attacking] = PLAYER->allow[Attacking_Shield]=false;
	PLAYER->allow[Sitting] = false;
}

void PlayeDiedState::Update(float deltaTime)
{
	/*if (PLAYER->currentAnim->_isFinished)
	{
		PLAYER->ChangeState(StateName::Standing);
	}*/
}

void PlayeDiedState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
}

StateName PlayeDiedState::GetState()
{
	return StateName::Die;
}

void PlayeDiedState::OnCollision(GameObject* entity, float deltaTime)
{
}
