#include "status.h"

status::status()
{// フォントハンドルの作成（サイズ24、太さ6、アンチエイリアス有効）
	normalFont = CreateFontToHandle(NULL, 24, 6, DX_FONTTYPE_ANTIALIASING);
	titleFont = CreateFontToHandle(NULL,48,8, DX_FONTTYPE_ANTIALIASING);
	valueFont = CreateFontToHandle(NULL, 28, 6, DX_FONTTYPE_ANTIALIASING);

	// 通常表示パネル用のフォント
	labelFont = CreateFontToHandle(NULL, 18, 4, DX_FONTTYPE_ANTIALIASING); // ラベル（HP, O2...）
	numFont = CreateFontToHandle(NULL, 22, 5, DX_FONTTYPE_ANTIALIASING); // 数値（999/999）

	ApplyStats();
}







status::~status()
{
	DeleteFontToHandle(normalFont);
	DeleteFontToHandle(titleFont);
	DeleteFontToHandle(valueFont);
	DeleteFontToHandle(labelFont);  
	DeleteFontToHandle(numFont);
}


int status::CalcHP(int hp_point) const
{
	if (hp_point <= 50)
		return (int)(hp_point * 1.07f);
	else
		return (int)(hp_point * 1.05f);
}

int status::CalcO2(int o2_point) const
{
	if (o2_point <= 50)
		return (int)(o2_point * 1.05f);
	else
		return (int)(o2_point * 1.025f);
}

int status::CalcStrength(int sp_point) const
{
	if (sp_point <= 50)
		return (int)(sp_point * 1.05f);
	else
		return (int)(sp_point * 1.025f);
}

int status::CalcPix(int pp_point) const
{
	if (pp_point <= 50)
		return (int)(pp_point * 1.05f);
	else
		return (int)(pp_point * 1.025f);
}

void status::ApplyStats()
{
	HP_MAX = CalcHP(Hp);
	O2_MAX = CalcO2(Op);
	strength = CalcStrength(Sp);
	pix = CalcPix(Pp);
}

bool status::IsButtonClicked(int btnX, int btnY, int btnW, int btnH, int mouseX, int mouseY) const
{
	return (mouseX >= btnX && mouseX <= btnX + btnW &&
		mouseY >= btnY && mouseY <= btnY + btnH);
}



void status::Update()
{
	if (!showUpgradeScreen) return;

	bool currentMouseLeft = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

	// クリック瞬間だけ処理
	if (currentMouseLeft && !prevMouseLeft)
	{
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);

		
		const int screenWidth = 1920;
		const int screenHeight = 1080;
		const int panW = 900;
		const int panH = 700;
		const int panX = (screenWidth - panW) / 2;  // 510
		const int panY = (screenHeight - panH) / 2;  // 190

		const int statusStartX = panX + 140;
		const int statusStartY = panY + 200;
		const int lineH = 70;
		const int btnW = 50;
		const int btnH = 50;
		const int btnOffsetX = 250; // ラベルから右にずらした位置

		// 各ステータスの [+] ボタン座標
		// HP
		int btnHpX = statusStartX + btnOffsetX;
		int btnHpY = statusStartY - btnH / 2;
		// O2
		int btnO2X = statusStartX + 300 + btnOffsetX;
		int btnO2Y = statusStartY - btnH / 2;
		// 筋力
		int btnSpX = statusStartX + btnOffsetX;
		int btnSpY = statusStartY + lineH - btnH / 2;
		// つるはし
		int btnPpX = statusStartX + 300 + btnOffsetX;
		int btnPpY = statusStartY + lineH - btnH / 2;

		// 鉱石が残っている場合のみ強化可能（鉱石1個 = 1ポイント）
		if (ore > 0)
		{
			if (IsButtonClicked(btnHpX, btnHpY, btnW, btnH, mouseX, mouseY))
			{
				Hp++;
				ore--;
				ApplyStats();
			}
			else if (IsButtonClicked(btnO2X, btnO2Y, btnW, btnH, mouseX, mouseY))
			{
				Op++;
				ore--;
				ApplyStats();
			}
			else if (IsButtonClicked(btnSpX, btnSpY, btnW, btnH, mouseX, mouseY))
			{
				Sp++;
				ore--;
				ApplyStats();
			}
			else if (IsButtonClicked(btnPpX, btnPpY, btnW, btnH, mouseX, mouseY))
			{
				Pp++;
				ore--;
				ApplyStats();
			}
		}
	}

	prevMouseLeft = currentMouseLeft;
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

	const int PANEL_X = 510;
	const int PANEL_Y = 190;
	const int PANEL_W = 900;
	const int PANEL_H = 700;
	const int COL1_X = PANEL_X + 60;   // 570 左列
	const int COL2_X = PANEL_X + 480;  // 990 右列
	const int ROW1_Y = PANEL_Y + 80;   // 270 1行目
	const int ROW2_Y = PANEL_Y + 180;  // 370 2行目
	const int VAL_OX = 130;            // ラベルから数値へのXオフセット
	const int BTN_OX = 280;            // ラベルから[+]へのXオフセット
	const int BTN_W = 60;
	const int BTN_H = 60;

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
	unsigned int ptColor = (ore > 0)
		? GetColor(100, 255, 100)
		: GetColor(200, 100, 100);
	DrawFormatStringToHandle(upgradePanelX + 30, upgradePanelY + 110, ptColor, valueFont, "鉱石（強化ポイント）残: %d", ore);

	
	//ステたすの位置
	int statusStartX = upgradePanelX + 140;//560-
	int statusStartY = upgradePanelY + 200;//300-
	
	
	unsigned int labelColor = GetColor(200, 200, 200);
	unsigned int valueColor = GetColor(255, 255, 255);
	unsigned int btnColor = (ore > 0)
		? GetColor(80, 200, 80)
		: GetColor(100, 100, 100);
	unsigned int btnLabel = GetColor(255, 255, 255);


	// HP
	DrawStringToHandle(COL1_X, ROW1_Y, "HP：", labelColor, titleFont);
	DrawFormatStringToHandle(COL1_X + VAL_OX, ROW1_Y, valueColor, titleFont, "%d", HP_MAX);
	DrawBox(COL1_X + BTN_OX, ROW1_Y, COL1_X + BTN_OX + BTN_W, ROW1_Y + BTN_H, btnColor, TRUE);
	DrawStringToHandle(COL1_X + BTN_OX + 15, ROW1_Y + 8, "+", btnLabel, titleFont);

	// O2
	DrawStringToHandle(COL2_X, ROW1_Y, "O2タンク：", labelColor, titleFont);
	DrawFormatStringToHandle(COL2_X + VAL_OX, ROW1_Y, valueColor, titleFont, "%d", O2_MAX);
	DrawBox(COL2_X + BTN_OX, ROW1_Y, COL2_X + BTN_OX + BTN_W, ROW1_Y + BTN_H, btnColor, TRUE);
	DrawStringToHandle(COL2_X + BTN_OX + 15, ROW1_Y + 8, "+", btnLabel, titleFont);


	// Strength
	DrawStringToHandle(COL1_X, ROW2_Y, "筋力：", labelColor, titleFont);
	DrawFormatStringToHandle(COL1_X + VAL_OX, ROW2_Y, valueColor, titleFont, "%d", strength);
	DrawBox(COL1_X + BTN_OX, ROW2_Y, COL1_X + BTN_OX + BTN_W, ROW2_Y + BTN_H, btnColor, TRUE);
	DrawStringToHandle(COL1_X + BTN_OX + 15, ROW2_Y + 8, "+", btnLabel, titleFont);
	// Pix
	DrawStringToHandle(COL2_X, ROW2_Y, "つるはし：", labelColor, titleFont);
	DrawFormatStringToHandle(COL2_X + VAL_OX, ROW2_Y, valueColor, titleFont, "%d", pix);
	DrawBox(COL2_X + BTN_OX, ROW2_Y, COL2_X + BTN_OX + BTN_W, ROW2_Y + BTN_H, btnColor, TRUE);
	DrawStringToHandle(COL2_X + BTN_OX + 15, ROW2_Y + 8, "+", btnLabel, titleFont);

	//強化ポイント
	
	DrawStringToHandle(COL2_X, PANEL_Y + 320, "残り：", ptColor, titleFont);
	DrawFormatStringToHandle(COL2_X, PANEL_Y + 390, ptColor, titleFont, "%dポイント", ore);
}

void status::DrawNormalStatus()
{
	int panW = 780;   // パネルの幅
	int panH = 70;    // パネルの高さ（細長く）
	int panX = 20;    // 左端からの距離
	int panY = 15;    // 上端からの距離
	int radius = 12;  // 角の丸み

	// 半透明の背景
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawRoundRect(panX, panY, panX + panW, panY + panH,
		radius, radius, GetColor(10, 10, 25), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 枠線（丸角）
	DrawRoundRect(panX, panY, panX + panW, panY + panH,
		radius, radius, GetColor(100, 140, 200), FALSE);

	
	// 列のX座標
	int col1X = panX + 20;   // BF
	int col2X = panX + 140;  // HP
	int col3X = panX + 300;  // O2
	int col4X = panX + 460;  // 石
	int col5X = panX + 620;  // 鉱石

	int labelY = panY + 8;   // ラベルのY（上段）
	int valueY = panY + 34;  // 数値のY（下段）

	unsigned int labelCol = GetColor(180, 210, 255);  // ラベルの色（青白）
	unsigned int whiteCol = GetColor(255, 255, 255);   // 数値の色（白）
	unsigned int hpCol = GetColor(255, 110, 110);   // HP（赤）
	unsigned int o2Col = GetColor(100, 200, 255);   // O2（水色）
	unsigned int stoneCol = GetColor(200, 200, 200);   // 石（グレー）
	unsigned int oreCol = GetColor(255, 210, 80);    // 鉱石（金）

	//  BF 
	DrawFormatStringToHandle(col1X, labelY, labelCol, labelFont, "BF");
	DrawFormatStringToHandle(col1X, valueY, whiteCol, numFont, "%d", BF);

	//  HP 
	DrawStringToHandle(col2X, labelY, "HP", labelCol, labelFont);
	DrawFormatStringToHandle(col2X, valueY, hpCol, numFont, "%d/%d", HP, HP_MAX);

	//  O2 
	DrawStringToHandle(col3X, labelY, "O2", o2Col, labelFont);
	DrawFormatStringToHandle(col3X, valueY, o2Col, numFont, "%d/%d", O2, O2_MAX);

	//  石 
	DrawStringToHandle(col4X, labelY, "石", labelCol, labelFont);
	DrawFormatStringToHandle(col4X, valueY, stoneCol, numFont, "%d/99", stone);

	//  鉱石 
	DrawStringToHandle(col5X, labelY, "鉱石", labelCol, labelFont);
	DrawFormatStringToHandle(col5X, valueY, oreCol, numFont, "%d", ore);

}
