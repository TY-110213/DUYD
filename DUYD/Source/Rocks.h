#pragma once
#include "../Library/GameObject.h"

class Rocks : public GameObject {
public:
	Rocks(int x, int y, int size);
	~Rocks();
	void Update() override;
	void Draw() override;
private:
	int x = 0;
	int y = 0;
	int size = 0;
};