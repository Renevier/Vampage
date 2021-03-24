#include "pch.h"
#include "MainMenuState.h"


void MainMenuState::InitBackground()
{
	this->background.setSize(Vector2f((float)this->window->getSize().x, (float)this->window->getSize().y));

	if (!this->backgroundTexture.loadFromFile("../Resources/Backgrounds/bakcground_menu_Vampage.png"))
		exit(0);

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::InitFont()
{
	if (!this->font.loadFromFile("../Resources/Fonts/BLOODY.ttf"))
		exit(0);
}

void MainMenuState::InitButton()
{
	this->buttons.emplace("NEW_GAME", new Button(100, 500, 250, 50,
		&this->font, "New game", 50,
		Color(255, 0, 0, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(250, 250, 250, 0), Color(20, 20, 20, 0)));

	this->buttons.emplace("BOSS", new Button(100, 600, 250, 50,
		&this->font, "Boss", 50,
		Color(255, 0, 0, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(250, 250, 250, 0), Color(20, 20, 20, 0)));

	this->buttons.emplace("EXIT", new Button(100, 700, 250, 50,
		&this->font, "Quit", 50,
		Color(255, 0, 0, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(250, 250, 250, 0), Color(20, 20, 20, 0)));

}

MainMenuState::MainMenuState(RenderWindow* _window, stack<State*>* _states)
	: State(_window, _states)
{
	this->InitBackground();
	this->InitFont();
	this->InitButton();
}

void MainMenuState::UpdateInput(const float& _dt)
{
}

void MainMenuState::UpdateButton()
{
	for (auto it : this->buttons)
		it.second->Update(this->mousePosView);

	if (this->buttons.at("NEW_GAME")->IsPressed())
		this->states->push(new GameState(this->window, this->states));

	if (this->buttons.at("BOSS")->IsPressed())
		this->states->push(new BossState(this->window, this->states));

	if (this->buttons.at("EXIT")->IsPressed())
		this->Quit = true;
}

void MainMenuState::Update(const float& _dt)
{
	this->UpdateMousePosition();
	this->CheckForQuit();
	this->UpdateButton();
}

void MainMenuState::RenderButton(RenderTarget* _target)
{
	for (auto it : this->buttons)
		it.second->Render(*_target);
}

void MainMenuState::Render(RenderTarget* _target)
{
	if (!_target)
		_target = this->window;

	_target->draw(this->background);

	this->RenderButton(_target);

	//print mouse potiton in the console
	/*system("CLS");
	cout << this->mousePosView.x << " " << this->mousePosView.y;*/
}

void MainMenuState::EndState()
{
}

void MainMenuState::CheckForQuit()
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
		this->Quit = true;
}

MainMenuState::~MainMenuState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;
}
