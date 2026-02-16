#pragma once
#pragma once
#include "../Library/GameObject.h"

class status : public GameObject

{
public:
	status();
	~status();
	void Update() override;
	void Draw();
	void ToggleUpgradeScreen();
	bool IsUpgradeScreenOpen() const { return showUpgradeScreen; }
private:
	int BF = 1;
	int HP = 999;
	int O2 = 100;
	int stone = 0;
	int ore = 0;
	int panelX = 10;
	int panelY = 10;
	int panelWidth = 400;// î¬ïù
	int panelHeight = 150;// î¬çÇÇ≥
	int strength = 999;
	int pix = 999;
	int upgradePoints = 10;
	bool showUpgradeScreen = false;

	int normalFont;
	int titleFont;
	int valueFont;
	void DrawUpgradeScreen();
	void DrawNormalStatus();
};

