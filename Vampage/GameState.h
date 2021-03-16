#pragma once
#include "State.h"
#include "Player.h"
#include "Enemy.h"
#include "Bonus.h"

class GameState :
    public State
{
private:    
    int points;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int cptEnemies;
    float timerForNextLevel;

    unique_ptr<Player> player;
    vector<unique_ptr<Enemy>> enemies;
    Bonus* bonus;
    RectangleShape endLevel;

    bool goToNextLevel;

private:
    void InitPlayer();
    void InitTexture();
    void InitVariables();
    void InitEndLevel();

public:
    GameState(RenderWindow* _window, stack<State*>* _states);
    ~GameState() = default;

    void DropBonus(float _x, float _y);
    void SpawnEnemy();
    void KillEnemy();
    bool PickedUpBonus(const float& _dt);

    virtual void UpdateInput(const float& _dt);
    void UpdateEnemies(const float& _dt);
    virtual void Update(const float& _dt);
    virtual void EndState();
    void PauseMenu();

    void RenderEnemies(RenderTarget* _target);
    void RenderPlayer(RenderTarget* _target);
    void RenderBonus(RenderTarget* _target);
    virtual void Render(RenderTarget* _target);
};

