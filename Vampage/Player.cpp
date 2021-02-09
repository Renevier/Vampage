#include "pch.h"
#include "Player.h"

void Player::InitShape()
{
	this->shape.setSize(Vector2f(50, 50));
	this->shape.setFillColor(Color::Blue);
	this->shape.setOrigin(Vector2f(this->shape.getGlobalBounds().width / 2, this->shape.getGlobalBounds().height / 2));
}

void Player::InitNoSpawnAera()
{
	this->noSpawnArea.setRadius(200.f);
	this->noSpawnArea.setOrigin(this->noSpawnArea.getRadius(), this->noSpawnArea.getRadius());
	this->noSpawnArea.setFillColor(Color::Transparent);
	this->noSpawnArea.setPosition(this->shape.getPosition());

	this->noSpawnArea.setOutlineThickness(1.f);
	this->noSpawnArea.setOutlineColor(Color::Green);
}

Player::Player(float _x, float _y, Vector2f _mousePosView)
{
	this->InitShape();
	this->InitPosition(_x, _y);
	this->InitNoSpawnAera();

	this->movementSpeed = 500.f;
}

Player::~Player()
{
}

void Player::Move(const float& _dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Z))
		this->shape.move(0, - this->movementSpeed * _dt);
	if (Keyboard::isKeyPressed(Keyboard::S))
		this->shape.move(0, this->movementSpeed * _dt);
	if (Keyboard::isKeyPressed(Keyboard::Q))
		this->shape.move(- this->movementSpeed * _dt, 0);
	if (Keyboard::isKeyPressed(Keyboard::D))
		this->shape.move(this->movementSpeed * _dt, 0);
}

void Player::Shoot(const float& _dt)
{
	bullets.push_back(make_unique<Bullet>(this->mousePosView,
		10.f, this->shape.getPosition().x, this->shape.getPosition().y));

	for (int i = 0; i < bullets.size(); i++) {
		this->bullets[i]->Update(_dt);
	}
}

void Player::Update(const float& _dt)
{
	this->Move(_dt);
	this->Shoot(_dt);

	this->UpdateNoSpawnArea();
}

void Player::UpdateNoSpawnArea()
{
	this->noSpawnArea.setPosition(this->shape.getPosition());
}

void Player::RenderBullets(RenderTarget& _target)
{
	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->Draw(_target);
}

void Player::Draw(RenderTarget& _target)
{
	_target.draw(this->shape);
	_target.draw(this->noSpawnArea);

	this->RenderBullets(_target);
}
