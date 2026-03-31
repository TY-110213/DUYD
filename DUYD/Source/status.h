#pragma once

#include <DxLib.h> 

class status 

{
public:
	status();
	~status();
	void Update();
	void Draw();
	void ToggleUpgradeScreen();
	bool IsUpgradeScreenOpen() const { return showUpgradeScreen; }

	void ReduceO2(int amount = 1);   // O2を減らす
	void RecoverO2();                // 酸素鉱石破壊時の回復（MAX/4）
	
	void TakeDamage(int amount = 30);  // HP直接ダメージ
	void AddStone(int amount = 1) { stone += amount; }
	bool UseStone() { if (stone <= 0)return false;stone--;return true; }
	int GetStone() const { return stone; }
	bool HasStone() const { return stone > 0; }

	
	bool o2TUTDone = false;
	bool oreTUTDone = false;
	void AddOre(int amount = 1) { ore += amount; }
	int GetOre() const { return ore; }

	int GetHP() const { return HP; }
	int GetO2() const { return O2; }
	int GetO2Max() const { return O2_MAX; }
	int GetStrength() const { return strength; }
	int GetPix() const { return pix; }
	int GetBF() const { return BF; }
	void AddBF() { BF++; }  // BFを1増やす
	bool IsGameOver() const { return HP <= 0; }
private:
	int pauseType = 0;
	int BF = 1;
	int HP = 3;
	int O2 = 30;
	int stone = 0;
	int ore = 0;
	int panelX = 10;
	int panelY = 10;
	int panelWidth = 400;
	int panelHeight = 150;
	bool isPaused = false;

	float o2Timer = 0.0f;       // 1秒カウント用
	float hpTimer = 0.0f;       // O2=0時のHPダメージ用カウント
	int Hp = 3;
	int Op = 29;
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

