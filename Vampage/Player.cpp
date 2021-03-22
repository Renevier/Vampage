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
	this->shootingLenght = 2.f;
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

		if (!this->bullets[i]->GetBounds().intersects(this->noSpawnArea.getGlobalBounds()))
		{
			if (i != 0)
				i--;

			this->bullets.erase(this->bullets.begin() + i);
		}
	}
}

void Player::Update(const float& _dt)
{
	/*system("CLS");
	cout << this->haveShield;*/

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
	_target.draw(this->noSpawnArea);
}
