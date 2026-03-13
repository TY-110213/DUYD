#pragma once
#include "../Library/GameObject.h"

class Game;

class Backs : public GameObject {
public:
	Backs(int size, Game* g);
	~Backs();
	void Update() override;
	void Draw() override;
private:
	int hImage[7];
	int size1 = 0;
	Game* gameRef;
};