#include "Tansakunosyo.h"
#include <DxLib.h>
#include "Screen.h"

int TansakuImage;

Tansakunosyo::Tansakunosyo()
{
	TansakuImage = LoadGraph("data/screen/’Tõ‚Ì‘.png");
}

Tansakunosyo::~Tansakunosyo()
{
}

void Tansakunosyo::Update()
{
}

void Tansakunosyo::Draw()
{
	//DrawString(0, 0, "’Tõ‚Ì‘", GetColor(255, 255, 255));
	DrawExtendGraph(0, 0, 1920, 1080, TansakuImage, TRUE);//¶ã(0,0)‚©‚ç‰E‰º(1920,1080)‚Ì”ÍˆÍ‚É‰æ‘œ‚ğˆø‚«L‚Î‚µ‚Ä•\¦‚·‚é@•¶š‚¢‚ç‚ê‚ñ
}
