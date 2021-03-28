#pragma once
#include "State.h"
#include "Player.h"
#include "Tool.h"
#include "Enemy.h"
#include "RangedEnnemy.h"
#include "BouncedEnemy.h"
#include "Boss.h"
#include "Bonus.h"
#include "LevelEnded.h"
#include "HUD.h"

class GameState :
    public State
{
private:  
    int level;
    int points;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int cptEnemies;
    float timerForNextLevel;

    HUD* hud;
    Player* player;
    vector<unique_ptr<Enemy>> enemies;
    unique_ptr<LevelEnded> levelEnded;
    Bonus* bonus;
    unique_ptr<Boss> boss;

    bool goToNextLevel;

private:
    void InitPlayer();
    void InitTexture();
    void InitVariables();
    void InitEndLevel();
    void InitHUD();

public:
    GameState(RenderWindow* _window, stack<State*>* _states);
    ~GameState();

    void DropBonus(float _x, float _y);
    void SpawnEnemy();
    void SpawnBoss();
    void KillEnemy();
    void PickedUpBonus(const float& _dt);

    virtual void UpdateInput(const float& _dt);
    void UpdateEnemies(const float& _dt);
    void UpdatePlayer(const float& _dt);
    virtual void Update(const float& _dt);
    virtual void EndState();
    void PauseMenu();

    void RenderEnemies(RenderTarget* _target);
    void RenderBoss(RenderTarget* _target);
    void RenderPlayer(RenderTarget* _target);
    void RenderBonus(RenderTarget* _target);
    virtual void Render(RenderTarget* _target);
};

