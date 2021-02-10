#pragma once
#include "State.h"
#include "Player.h"
#include "Enemy.h"
class GameState :
    public State
{
private:
    int points;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;

    unique_ptr<Player> player;
    vector<shared_ptr<Enemy>> enemies;
    CircleShape spawnArea;

private:
    void InitPlayer();
    void InitTexture();
    void InitVariables();
    virtual void InitView();
    void InitSpawnArea();

public:
    GameState(RenderWindow* _window, stack<State*>* _states);
    ~GameState();

    void SpawnEnemy();
    void KillEnemy();
    void UpdateView();
    void UpdateSpawnArea();
    virtual void UpdateInput(const float& _dt);
    void UpdateEnemies(const float& _dt);
    virtual void Update(const float& _dt);
    virtual void EndState();
    void PauseMenu();

    void RenderSpawnArea(RenderTarget* _target);
    void RenderEnemies(RenderTarget* _target);
    void RenderPlayer(RenderTarget* _target);
    virtual void Render(RenderTarget* _target);
};

