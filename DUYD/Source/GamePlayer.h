#pragma once
#include "../Library/GameObject.h"
#include "Game.h"

class GamePlayer : public GameObject {
public:
	GamePlayer(float x, float y, int size1);
	~GamePlayer();
	void Update() override;
	void Draw() override;
	void SetMap(Game* m);
	float px = 0;
	float py = 0;
	float GetX() const { return px; }
	float GetY() const { return py; }
private:
	int hImage = 0;
	
	float width = 0;
	float height = 0;
	int size = 0;
	
	Game* game;
};