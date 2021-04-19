#pragma once
#include "State.h"
#include "MainMenuState.h"
#include "Player.h"
#include "Tool.h"
#include "Enemy.h"
#include "RangedEnnemy.h"
#include "BouncedEnemy.h"
#include "Boss.h"
#include "Bonus.h"
#include "LevelEnded.h"
#include "HUD.h"
#include "Pause.h"
#include "DeathScreen.h"

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
    unique_ptr<Pause> pause;
    unique_ptr<DeathScreen> deathScreen;

    bool goToNextLevel;
    bool bPause;
    bool isDead;

private:
    void InitPlayer();
    void InitTexture();
    void InitVariables();
    void InitEndLevel();
    void InitHUD();
    void InitPause();
    void InitPauseButtons();
    void InitDeathScreen();
    void InitDeathScreenButtons();

public:
    GameState(RenderWindow* _window, stack<State*>* _states);
    ~GameState();

    void DropBonus(float _x, float _y);
    void SpawnEnemy();
    void SpawnBoss();
    void KillEnemy();
    void PickedUpBonus(const float& _dt);

    void UpdatePauseButton();
    void UpdateDeathButton();
    virtual void UpdateInput(const float& _dt);
    void UpdateEnemies(const float& _dt);
    void UpdatePlayer(const float& _dt);
    virtual void Update(const float& _dt);
    virtual void EndState();
    void PauseMenu();
    void CheatCode();

    void RenderEnemies(RenderTarget* _target);
    void RenderBoss(RenderTarget* _target);
    void RenderPlayer(RenderTarget* _target);
    void RenderBonus(RenderTarget* _target);
    virtual void Render(RenderTarget* _target);
};

