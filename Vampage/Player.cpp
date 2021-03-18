#include "pch.h"
#include "Player.h"

void Player::InitShape()
{
	if (!this->playerTexture.loadFromFile("../Resources/Sprite/PNG/Hitman_1/hitman1_gun.png"))
		exit(0);

	this->shape.setTexture(&playerTexture);
	
	this->shape.setSize(Vector2f(
		this->shape.getTextureRect().height,
		this->shape.getTextureRect().width
	));

	this->shape.setOrigin(Vector2f(
		this->shape.getGlobalBounds().width / 2,
		this->shape.getGlobalBounds().height / 2
	));
}

void Player::InitNoSpawnAera()
{
	this->noSpawnArea.setRadius(500.f);
	this->noSpawnArea.setOrigin(
		this->noSpawnArea.getRadius(),
		this->noSpawnArea.getRadius()
	);

	this->noSpawnArea.setFillColor(Color::Transparent);
	this->noSpawnArea.setPosition(this->shape.getPosition());

	/*this->noSpawnArea.setOutlineThickness(1.f);
	this->noSpawnArea.setOutlineColor(Color::Green);*/
}

Player::Player(Vector2f* _mousePosView, float _x, float _y) :
	nbDashMax(3), nbDash(nbDashMax)
{
	this->InitShape();
	this->InitPosition(_x, _y);
	this->InitNoSpawnAera();

	this->movementSpeed = 500.f;
	this->mousePosView = _mousePosView;
	this->shootingLenght = 500.f;
}

Player::~Player()
{
	//delete bonus
	for (auto it : this->bonus)
		delete it;
}

void Player::AddBonus(Bonus* _bonus)
{
	this->bonus.push_back(_bonus);
}

void Player::Move(const float& _dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Z))
	{
		this->velocity.y = 0.f;

		this->shape.move(0, -this->movementSpeed * _dt);
		this->velocity.x = 0;
		this->velocity.y -= this->movementSpeed * _dt;
	}

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		this->velocity.y = 0.f;

		this->shape.move(0, this->movementSpeed * _dt);
		this->velocity.x = 0;
		this->velocity.y += this->movementSpeed * _dt;
	}

	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		this->velocity.x = 0.f;

		this->shape.move(-this->movementSpeed * _dt, 0);
		this->velocity.x -= this->movementSpeed * _dt;
		this->velocity.y = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		this->velocity.x = 0.f;

		this->shape.move(this->movementSpeed * _dt, 0);
		this->velocity.x += this->movementSpeed * _dt;
		this->velocity.y = 0;
	}
}

void Player::Dash(const float& _dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Space) && this->nbDash > 0 && this->timeBetweenDash.asSeconds() >= 2)
	{
		this->timeBetweenDash = this->clockDash.restart();
		this->shape.move(this->velocity.x * 2 * _dt, this->velocity.y * 2 * _dt);
		this->nbDash--;
	}

	if (Keyboard::isKeyPressed(Keyboard::Numpad2))
	{
		this->nbDash = 10;
	}
}

void Player::Shoot(const float& _dt)
{
	this->timeBetweenShoot += _dt;

	if (this->timeBetweenShoot >= .1f)
	{
		bullets.push_back(make_shared<Bullet>(*this->mousePosView,
			this->shape.getPosition().x, this->shape.getPosition().y));

		this->timeBetweenShoot = 0;
	}

	for (int i = 0; i < this->bullets.size(); i++) {
		this->bullets[i]->Update(_dt);

		Vector2f destroyBulletPos = Vector2f(
			this->bullets[i]->GetShape().getPosition().x - this->shape.getPosition().x,
			this->bullets[i]->GetShape().getPosition().y - this->shape.getPosition().y
		);

		if (abs(destroyBulletPos.x) + abs(destroyBulletPos.y) >= this->shootingLenght)
		{
			if (i != 0)
				i--;

			this->bullets.erase(this->bullets.begin() + i);
		}
	}
}

void Player::Update(const float& _dt)
{
	this->timeBetweenDash = this->clockDash.getElapsedTime();

	this->Move(_dt);
	this->Shoot(_dt);
	this->Dash(_dt);

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
	this->RenderBullets(_target);

	_target.draw(this->shape);
	_target.draw(this->noSpawnArea);
}
