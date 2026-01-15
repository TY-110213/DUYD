#pragma once
#include  "../Library/SceneBase.h"

class TUT :public SceneBase
{public: 
	TUT();
	~TUT();
	void Update() override;
	void Draw() override;
	int image;
};

