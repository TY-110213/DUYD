#pragma once
#include "../Library/GameObject.h"

class Enemy : public GameObject {
public:
	Enemy(int size);
	~Enemy();
	void Update() override;
	void Draw() override;
private:
	int x;
	int y;
};