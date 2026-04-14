#pragma once
#include  "../Library/SceneBase.h"
class Tansakunosyo : public SceneBase
{public:
	Tansakunosyo();
	~Tansakunosyo();
	void Update() override;
	void Draw() override;
	int TitleBGM;
	int buttonSE;
	int reachedBF = 0;
	int killCount = 0;
	int breakRocks = 0;
	int fontTitle;
	int fontResult;
	int fontLabel;
	int highScoreBF = 0;
	int highScoreKill = 0;
	int highScoreBreak = 0;
};

