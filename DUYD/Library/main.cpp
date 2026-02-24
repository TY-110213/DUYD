/// <summary>
/// CoGフレームワーク
/// WinMain()から始まります
/// </summary>
/// <author>N.Hanai</author>
/// 
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__);
#else
#define DBG_NEW new
#endif

#define IMGUI 1
#include <DxLib.h>
#include "App.h"
#include "../Source/Screen.h"
#include "../ImGui/imgui_impl_dxlib.hpp"

#define CoGVersion "4.5"

const char* Version() {
	return CoGVersion;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(1920, 1080, 32);
	SetOutApplicationLogValidFlag(FALSE);

	SetMainWindowText(Screen::WINDOW_NAME);
	SetWindowSizeExtendRate(Screen::WINDOW_EXTEND);
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SetWaitVSyncFlag(FALSE);  // 手動FPS制限のためVSync無効
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	SetHookWinProc([](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT /*CALLBACK*/
		{
			SetUseHookWinProcReturnValue(FALSE);
			return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		});
#if IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.Fonts->AddFontFromFileTTF(u8"c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
	ImGui_ImplDXlib_Init();
#endif
	const int TARGET_MS = 1000 / (int)Screen::FRAME_RATE;  // Screen.hのFRAME_RATEを使用

	AppInit();  // Time::Init()はApp.cpp内で呼ばれる

	while (true) {
#if IMGUI
		ImGui_ImplDXlib_NewFrame();
		ImGui::NewFrame();
#endif
		int frameStart = GetNowCount();  // FPS制限用の基準時刻

		AppUpdate();

		if (ProcessMessage() == -1 || AppIsExit())
		{
			break;
		}
		ScreenFlip();
		ClearDrawScreen();
		AppDraw();  // Time::Refresh()はApp.cpp内で呼ばれる
#if IMGUI
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDXlib_RenderDrawData();
#endif
		RefreshDxLibDirect3DSetting();
#if IMGUI
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
#endif
		// FPS制限（Screen::FRAME_RATEに基づく）
		int elapsed = GetNowCount() - frameStart;
		if (elapsed < TARGET_MS)
		{
			WaitTimer(TARGET_MS - elapsed);
		}
	}

	AppRelease();  // Time::Release()はApp.cpp内で呼ばれる
#if IMGUI
	ImGui_ImplDXlib_Shutdown();
	ImGui::DestroyContext();
#endif
	DxLib_End();
#ifdef _DEBUG
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}
