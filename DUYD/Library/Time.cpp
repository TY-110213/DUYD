#include "time.h"
#include <Windows.h>
#include <DxLib.h>
namespace {
	LARGE_INTEGER freq;
	LARGE_INTEGER current;
	float deltaTime;
	float refreshRate;
};

void Time::Init()
{
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&current);

	deltaTime = 1.0f / 60.0f;
}

void Time::Refresh()
{
	LARGE_INTEGER last = current;
	QueryPerformanceCounter(&current);
	float dt = static_cast<float >(current.QuadPart - last.QuadPart) / freq.QuadPart;
	if (dt > 0.1f) dt = 1.0f / 60.0f;
	deltaTime = dt;  // Å© Ç±ÇÍÇ…Ç»Ç¡ÇƒÇ¢ÇÈÇ©ämîF
}

float Time::DeltaTime()
{
	return deltaTime;
}

void Time::Release()
{
}