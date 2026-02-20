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

	void AddStone(int amount = 1) { stone += amount; }
	bool UseStone() { if (stone <= 0)return false;stone--;return true; }
	int GetStone() const { return stone; }
	bool HasStone() const { return stone > 0; }

	void AddOre(int amount = 1) { ore += amount; }
	int GetOre() const { return ore; }

	int GetHP() const { return HP; }
	int GetO2() const { return O2; }
	int GetO2Max() const { return O2_MAX; }
	int GetStrength() const { return strength; }
	int GetPix() const { return pix; }

private:
	int BF = 1;
	int HP = 3;
	int O2 = 30;
	int stone = 0;
	int ore = 0;
	int panelX = 10;
	int panelY = 10;
	int panelWidth = 400;
	int panelHeight = 150;

	int Hp = 3;
	int Op = 30;
	int Sp = 1;
	int Pp = 1;
	int strength = 1;
	int pix = 1;
	bool showUpgradeScreen = false;
	int HP_MAX = 999;
	int O2_MAX = 100;

	int normalFont;
	int titleFont;
	int valueFont;
	int labelFont;  
	int numFont;     

	int CalcHP(int hp_point) const;
	int CalcO2(int o2_point) const;
	int CalcStrength(int sp_point) const;
	int CalcPix(int pp_point) const;

	void ApplyStats();

	bool IsButtonClicked(int btnX, int btnY, int btnW, int btnH, int mouseX, int mouseY) const;

	void DrawUpgradeScreen();
	void DrawNormalStatus();
	bool prevMouseLeft = false;
};

