#include "MainMenuState.h"

void MainMenuState::InitKeybinds()
{
}

void MainMenuState::InitBackground()
{
	this->background.setSize(Vector2f((float)this->window->getSize().x, (float)this->window->getSize().y));

	if (!this->backgroundTexture.loadFromFile("../Ressources/Background/backgound_menu.png"))
		exit(0);

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::InitFont()
{
	if (!this->font.loadFromFile("../Ressources/Font/rpgFont.ttf"))
		exit(0);
}

void MainMenuState::InitButton()
{
	this->buttons.emplace("NEW_GAME", new Button(100, 420, 250, 50,
		&this->font, "New game", Color::White, Color::Green, Color::Red));

	this->buttons.emplace("EXIT", new Button(100, 700, 250, 50,
		&this->font, "Quit", Color::White, Color::Green, Color::Red));

}

MainMenuState::MainMenuState(RenderWindow* _window, map<string, int>* _supportedKeys, stack<State*>* _states)
	: State(_window, _supportedKeys, _states)
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
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));

	//if (this->buttons.at("LOAD_GAME")->IsPressed())

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
		it.second->Render(_target);
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
