#include "status.h"

status::status()
{// フォントハンドルの作成（サイズ24、太さ6、アンチエイリアス有効）
	normalFont = CreateFontToHandle(NULL, 24, 6, DX_FONTTYPE_ANTIALIASING);
	titleFont = CreateFontToHandle(NULL,48,8, DX_FONTTYPE_ANTIALIASING);
	valueFont = CreateFontToHandle(NULL, 28, 6, DX_FONTTYPE_ANTIALIASING);
}

status::~status()
{
	DeleteFontToHandle(normalFont);
	DeleteFontToHandle(titleFont);
	DeleteFontToHandle(valueFont);
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
	else {
		DrawNormalStatus();
	}
}

void status::ToggleUpgradeScreen()
{
	showUpgradeScreen = !showUpgradeScreen;
}

void status::DrawUpgradeScreen()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,120);
	DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int screenWidth = 1920;
	int screenHeight = 1080;
	int upgradePanelWidth = 900;
	int upgradePanelHeight = 700;
	int upgradePanelX = (screenWidth - upgradePanelWidth) / 2;
	int upgradePanelY = (screenHeight - upgradePanelHeight) / 2;

	//アップグレード画面背景
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);
	DrawBox(upgradePanelX, upgradePanelY, upgradePanelX + upgradePanelWidth, upgradePanelY + upgradePanelHeight, GetColor(30, 40, 60), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//枠
	DrawBox(upgradePanelX, upgradePanelY, upgradePanelX + upgradePanelWidth, upgradePanelY + upgradePanelHeight,
		GetColor(150, 180, 220), FALSE);
	//強化ポイント
	int pointsX = upgradePanelX + upgradePanelWidth / 2 - 280;//700 -
	int pointsY = 300;
	DrawFormatStringToHandle(880, 630, GetColor(100, 255, 100), titleFont,
		"強化ポイント: %d", upgradePoints);

	
	//ステたすの位置
	int statusStartX = upgradePanelX + 140;//560-
	int statusStartY = pointsY + 100;//300-
	int lineHeight = 70;
	unsigned int labelColor = GetColor(200, 200, 200);
	unsigned int valueColor = GetColor(255, 255, 255);
	// HP
	DrawStringToHandle(statusStartX, statusStartY, "HP:", labelColor, titleFont);
	DrawFormatStringToHandle(statusStartX + 100, statusStartY, valueColor, titleFont, "%d", HP);

	// O2
	DrawStringToHandle(statusStartX + 300, statusStartY , "O2タンク:", labelColor, titleFont);
	DrawFormatStringToHandle(statusStartX + 550 , statusStartY , valueColor, titleFont, "%d", O2);//Y200

	// Strength
	DrawStringToHandle(statusStartX - 47, statusStartY + lineHeight , "筋力:", labelColor, titleFont);
	DrawFormatStringToHandle(statusStartX + 100, statusStartY + lineHeight , valueColor, titleFont, "%d", strength);

	// Pix
	DrawStringToHandle(statusStartX + 300, statusStartY + lineHeight , "つるはし:", labelColor, titleFont);
	DrawFormatStringToHandle(statusStartX + 550, statusStartY + lineHeight , valueColor, titleFont,"%d", pix);//420 +
}

void status::DrawNormalStatus()
{
	

}
