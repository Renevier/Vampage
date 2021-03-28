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

	this->noSpawnArea.setOutlineThickness(1.f);
	this->noSpawnArea.setOutlineColor(Color::Green);
}

Player::Player(Vector2f* _mousePosView, float _x, float _y) :
	nbDashMax(3), nbDash(nbDashMax)
{
	this->InitShape();
	this->InitPosition(_x, _y);
	this->InitNoSpawnAera();

	this->movementSpeed = 500.f;
	this->mousePosView = _mousePosView;
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
		this->dir = DIRECTION::UP;
		this->velocity.y = 0.f;

		this->shape.move(0, -this->movementSpeed * _dt);
		this->velocity.x = 0;
		this->velocity.y -= this->movementSpeed * _dt;
	}

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		this->dir = DIRECTION::DOWN;
		this->velocity.y = 0.f;

		this->shape.move(0, this->movementSpeed * _dt);
		this->velocity.x = 0;
		this->velocity.y += this->movementSpeed * _dt;
	}

	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		this->dir = DIRECTION::LEFT;
		this->velocity.x = 0.f;

		this->shape.move(-this->movementSpeed * _dt, 0);
		this->velocity.x -= this->movementSpeed * _dt;
		this->velocity.y = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		this->dir = DIRECTION::RIGHT;
		this->velocity.x = 0.f;

		this->shape.move(this->movementSpeed * _dt, 0);
		this->velocity.x += this->movementSpeed * _dt;
		this->velocity.y = 0;
	}

	this->Dash(_dt);
}

void Player::Dash(const float& _dt)
{
	if (IsDirectionPressed(sf::Keyboard::Key::LShift) && this->nbDash > 0 && this->timeBetweenDash >= .2f)
	{
		this->dash = true;
		this->timeBetweenDash = 0.f;
		this->nbDash--;
		this->isInvu = true;

		if (this->dir == DIRECTION::UP)
			this->shape.move(0, -this->movementSpeed * 10 * _dt);

		if (this->dir == DIRECTION::RIGHT)
			this->shape.move(this->movementSpeed * 10 * _dt, 0);

		if (this->dir == DIRECTION::LEFT)
			this->shape.move(-this->movementSpeed * 10 * _dt, 0);

		if (this->dir == DIRECTION::DOWN)
			this->shape.move(0, this->movementSpeed * 10 * _dt);
	}

	if (this->dash && this->timeBetweenDash >= 1.f)
	{
		this->dash = false;
		this->timeBetweenDash = 0;
	}

	if (this->nbDash < this->nbDashMax)
	{
		this->dashRecover += _dt;

		if (this->dashRecover >= 1.f)
		{
			this->nbDash++;
			this->dashRecover = 0.f;
		}
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

		float distance = sqrt(
			pow(this->shape.getPosition().x - this->bullets[i]->GetShape().getPosition().x, 2) +
			pow(this->shape.getPosition().y - this->bullets[i]->GetShape().getPosition().y, 2)
		);

		if (distance >= this->noSpawnArea.getRadius())
			this->bullets.erase(this->bullets.begin() + i);
	}
}

void Player::Update(const float& _dt)
{
	this->timeBetweenDash += _dt;

	this->Move(_dt);
	this->Shoot(_dt);

	this->UpdateNoSpawnArea();

	if (this->isInvu)
		this->timerInvu += _dt;

	if (this->timerInvu >= 45.f * _dt)
	{
		this->timerInvu = 0.f;
		this->isInvu = false;
	}
}

void Player::UpdateNoSpawnArea()
{
	this->noSpawnArea.setPosition(this->shape.getPosition());
}

void Player::CheckBonus()
{
	for (auto& it : this->bonus)
	{
		if (it->GetEffect() == BONUS_EFFECT::SHIELD && !this->haveShield)
			this->haveShield = true;
		else if (it->GetEffect() == BONUS_EFFECT::SHIELD && this->haveShield)
			this->lifePoint++;

		if (it->GetEffect() == BONUS_EFFECT::DASH_MAX)
			this->nbDashMax = 5;
		else
			this->nbDashMax = 3;

		if (it->GetEffect() == BONUS_EFFECT::SHOOTING_DISTANCE)
		{
			this->noSpawnArea.setRadius(550.f);

			this->noSpawnArea.setOrigin(
				this->noSpawnArea.getRadius(),
				this->noSpawnArea.getRadius()
			);
		}
	}
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
	//_target.draw(this->noSpawnArea);
}
