#pragma once
#include "../Library/SceneBase.h"
class GameOverScene : public SceneBase
{
public:
	GameOverScene();
	~GameOverScene();
	void Update() override;
	void Draw() override;

private:
	int reachedBF = 0;
	int killCount = 0;
	int breakRocks = 0;
	bool isHighScore = false;

	int bgImage = -1;
	int fontTitle;
	int fontResult;
	int fontLabel;

	bool prevMouseLeft = false;
};

