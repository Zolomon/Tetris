
#include <Windows.h>
#include <tchar.h>
#include "Settings.h"
#include "Game.h"
#include "Application.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

std::shared_ptr<Game> game;

void Update(double deltaTime, MSG* msg);
void Render();

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
        WS_OVERLAPPEDWINDOW,
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
	game->InitializeGraphics(hwnd);
	game->Start();

    MSG msg = { 0 };
	Application app(game);

    const double FRAMES_PER_SEC = 60.0;
    const double SEC_PER_UPDATE = 1.0 / FRAMES_PER_SEC;
		
    auto previousTime = Settings::Window::Clock.now();
    while (Settings::Window::IsRunning)
    {
        auto currentTime = Settings::Window::Clock.now();
        auto deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - previousTime).count();
        previousTime = currentTime;

		app.update(deltaTime);
        //Update(deltaTime, &msg);
        //Render();

        auto msToNextFrame = static_cast<int>((SEC_PER_UPDATE - deltaTime) * 1000.0);
        if (msToNextFrame > 0)
        {
            Sleep(msToNextFrame);
        }
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Update(double deltaTime, MSG* msg)
{
    while (PeekMessage(msg, NULL, NULL, NULL, PM_REMOVE))
    {
        if (msg->message == WM_QUIT)
        {
            Settings::Window::IsRunning = false;
        }

        TranslateMessage(msg);
        DispatchMessage(msg);
    }

    game->Update(deltaTime);
}

void Render()
{
    game->Render(1.0f);
}
