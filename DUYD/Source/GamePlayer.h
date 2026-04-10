#pragma once
#include "../Library/GameObject.h"
#include "Game.h"
#include "GlobalStatus.h"
#include "Gamemapadapter.h"
#include <vector>

class Stone;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class GamePlayer : public GameObject {
public:
    GamePlayer(float x, float y, int size1);
    ~GamePlayer();
    void Update() override;
    void Draw()   override;
    void SetMap(Game* m);
    float px = 0;
    float py = 0;
    float GetX() const { return px; }
    float GetY() const { return py; }
    bool isStairs = false;
    float invincibleTimer = 0.0f;//無敵時間
    static constexpr float INVINCIBLE_TIME = 1.0f;
    Direction GetDir() const {
        return dir;}
private:
    int hImage = 0;
    float width = 0;
    float height = 0;
    int size = 0;
    int count = 0;
    int count2 = 1;
    int count3 = 0;
    int count4 = 0;
    bool isBreak = false;
    bool move = false;
    Game* game;
    Direction dir = DOWN;
    bool prevHKey = false;
    bool prevLKey = false;

    std::vector<Stone*> stones;
    float throwCoolTimer = 0.0f;
    static constexpr float THROW_COOLTIME = 0.3f;
    //右クリック長押し防止
    bool  prevRightDown = false;   // 前フレームの右クリック状態
    int   rightPressStartTime = 0; // 右クリック押し始めの時刻(ms)
    GameMapAdapter* mapAdapter = nullptr;
    float o2DamageTimer = 0.0f;
    float O2_DMAGE_INTERVAL = 1.0f;
    int Throw;
    int SEHandle[7];
    int stepcount = 0;


};