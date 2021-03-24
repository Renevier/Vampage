#include "pch.h"
#include "BossState.h"

void BossState::InitPlayer()
{
	this->player = new Player(&this->mousePosView, this->window->getSize().x / 2, this->window->getSize().y / 2);
}

void BossState::InitBoss()
{
	this->boss = make_unique<Boss>(this->window, this->window->getSize().x / 2,
		this->window->getSize().y / 2, this->player);
}

BossState::BossState(RenderWindow* _window, stack<State*>* _states)
	:State(_window, _states)
{
	this->InitPlayer();
	this->InitBoss();
}

void BossState::UpdateInput(const float& _dt)
{
}

void BossState::Update(const float& _dt)
{
	this->player->Update(_dt);
	this->boss->Update(_dt);
}

void BossState::Render(RenderTarget* _target)
{
	if (!_target)
		_target = this->window;

	this->player->Draw(*_target);
	this->boss->Draw(*_target);
}

void BossState::EndState()
{
}
