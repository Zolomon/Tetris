
#include <Windows.h>
#include <tchar.h>
#include "Settings.h"
#include "Game.h"
#include "Application.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

std::shared_ptr<Game> game;

void ProcessInput(HWND hwnd, MSG* msg);

void Update(double deltaTime);

void Render(double deltaTime);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	wchar_t className[] = _T("TetrisClass");
	wchar_t windowName[] = _T("Tetris");

	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;

	RegisterClass(&wc);

	HWND hwnd = CreateWindow(
		className,
		windowName,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		static_cast<int>(Settings::Window::StartPosition.x),
		static_cast<int>(Settings::Window::StartPosition.y),
		static_cast<int>(Settings::Window::Size.x),
		static_cast<int>(Settings::Window::Size.y),
		NULL,
		NULL,
		hInstance,
		NULL
		);

	UpdateWindow(hwnd);

	ShowWindow(hwnd, nCmdShow);

	game = std::make_shared<Game>();

	game->game = game;
	game->initializeGraphics(hwnd);
	game->start();

	MSG msg = { 0 };


	const double FRAMES_PER_SEC = 60.0;
	const double SEC_PER_UPDATE = 1.0 / FRAMES_PER_SEC;

	auto previousTime = Settings::Window::Clock.now();

	while (Settings::Window::IsRunning)
	{
		auto currentTime = Settings::Window::Clock.now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - previousTime).count();

		previousTime = currentTime;

		ProcessInput(hwnd, &msg);

		Update(deltaTime);

		Render(deltaTime);

		auto msToNextFrame = static_cast<int>((SEC_PER_UPDATE - deltaTime) * 1000.0);

		if (msToNextFrame > 0)
		{
			Sleep(msToNextFrame);
		}
	}
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'S':
			game->addCommand(Command::Down);

			break;
		case 'W':
			game->addCommand(Command::Up);

			break;
		case 'A':
			game->addCommand(Command::Left);

			break;
		case 'D':
			game->addCommand(Command::Right);

			break;
		case ' ':
			game->addCommand(Command::Space);

			break;
		default:
			break;
		}
		break;
	case WM_CHAR:
	{
		if (wParam == VK_ESCAPE)
		{
			//PostQuitMessage(0);
			game->addCommand(Command::Esc);
			//return 0;
		}
		else if (wParam == VK_RETURN)
		{
			game->addCommand(Command::Enter);
		}
	}
	case WM_ERASEBKGND:
		return 1;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void ProcessInput(HWND hwnd, MSG* msg)
{
	while (PeekMessage(msg, NULL, NULL, NULL, PM_REMOVE)) {
		if (msg->message == WM_QUIT) {
			Settings::Window::IsRunning = false;
		}

		TranslateMessage(msg);
		DispatchMessage(msg);
	}
}

void Update(double deltaTime)
{
	game->update(deltaTime);
}

void Render(double deltaTime)
{
	game->render(deltaTime);
}
