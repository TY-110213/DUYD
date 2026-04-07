#pragma once
#include "../Library/GameObject.h"
#include "GlobalStatus.h"

class StatusDrawer : public GameObject {
public:
	StatusDrawer()
	{
		SetDrawOrder(-200);
		
	}

	void Update() override {}

	void Draw() override
	{
		GlobalStatus::Get().Draw();
	}
};



