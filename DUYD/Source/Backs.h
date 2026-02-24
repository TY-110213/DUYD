#pragma once
#pragma once
#include "../Library/GameObject.h"
#include "PlayScene.h"

class Backs : public GameObject {
public:
	Backs(int size);
	~Backs();
	void Update() override;
	void Draw() override;
private:
	int hImage[7];
	int size1 = 0;
};