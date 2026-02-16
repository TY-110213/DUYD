#pragma once

class TUT;

class Stone
{
public:
	Stone(float startX, float startY, int dir, TUT* map);
	~Stone();
	void Update();
	void Draw(int cameraX, int cameraY);
	bool IsActive() const { return active; }

private:
	float x, y;
	int direction;
	bool active;
	TUT* tutmap;

	static constexpr float SPEED = 5.0f;
	static constexpr int  STONE_SIZE = 32; //Î‚Ì‘å‚«‚³

	int hImage;
};

