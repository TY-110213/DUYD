#include "status.h"

status::status()
{

}

status::~status()
{
}

void status::Update()
{
	
}
void status::Draw()
{
	if (showUpgradeScreen)
	{
		DrawUpgradeScreen();
	}
	
}

void status::ToggleUpgradeScreen()
{
	showUpgradeScreen = !showUpgradeScreen;
}

void status::DrawUpgradeScreen()
{
}

void status::DrawNormalStatus()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int screenWidth = 1920;
	int screenHeight = 1080;
	int upgradePanelWidth = 800;
	int upgradePanelHeight = 600;
	int upgradePanelX = (screenWidth - upgradePanelWidth) / 2;
	int upgradePanelY = (screenHeight - upgradePanelHeight) / 2;
	
//アップグレード画面背景
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 250);
	DrawBox(upgradePanelX, upgradePanelY, upgradePanelX + upgradePanelWidth, upgradePanelY + upgradePanelHeight, GetColor(30, 40, 60), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//枠
	DrawBox(upgradePanelX,upgradePanelY, upgradePanelX + upgradePanelWidth, upgradePanelY + upgradePanelHeight,
		GetColor(150, 180, 220), FALSE);
//強化ポイント
	int pointsX = upgradePanelX + upgradePanelWidth / 2 - 120;
	int pointsY = 800;
	DrawFormatString(pointsX, pointsY, GetColor(100, 255, 100),
		"Remaining Points: %d", upgradePoints);

	//ステたすの位置
	int statusStartX = upgradePanelX + 80;
	int statusStartY = pointsY + 60;
	int lineHeight = 70;
	unsigned int labelColor = GetColor(200, 200, 200);
	unsigned int valueColor = GetColor(255, 255, 255);
	// HP
	DrawString(statusStartX, statusStartY, "HP:", labelColor);
	DrawFormatString(statusStartX + 150, statusStartY, valueColor, "%d", HP);

	// O2
	DrawString(statusStartX, statusStartY + lineHeight, "O2:", labelColor);
	DrawFormatString(statusStartX + 150, statusStartY + lineHeight, valueColor, "%d", O2);

	// Strength
	DrawString(statusStartX, statusStartY + lineHeight * 2, "Strength:", labelColor);
	DrawFormatString(statusStartX + 150, statusStartY + lineHeight * 2, valueColor, "%d", strength);

	// Pix
	DrawString(statusStartX, statusStartY + lineHeight * 3, "Pix:", labelColor);
	DrawFormatString(statusStartX + 150, statusStartY + lineHeight * 3, valueColor, "%d", pix);

}
