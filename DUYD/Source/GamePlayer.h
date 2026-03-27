#pragma once
#include "../Library/GameObject.h"
#include "Game.h"

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
    float invincibleTimer = 0.0f;//–³“GŽžŠÔ
    static constexpr float INVINCIBLE_TIME = 1.0f;
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
};