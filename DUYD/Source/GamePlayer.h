#pragma once
#include "../Library/GameObject.h"
#include "Game.h"

class GamePlayer : public GameObject {
public:
	GamePlayer(float x, float y, int size1);
	~GamePlayer();
	void Update() override;
	void Draw() override;
private:
	int hImage = 0;
	float px = 0;
	float py = 0;
	float width = 0;
	float height = 0;
	int size = 0;
	Game* game;
};