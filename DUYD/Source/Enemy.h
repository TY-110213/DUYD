#pragma once
#include "../Library/GameObject.h"
#include "IMap.h"


class Enemy : public GameObject {
public:
	Enemy(float x, float y, int size);
	~Enemy();
	void Update() override;
	void Draw() override;
private:
	float Ex;
	float Ey;
	int hImage;
	int Esize;
};