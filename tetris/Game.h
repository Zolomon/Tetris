#pragma once

#include <Windows.h>
#include <iterator>
#include <vector>
#include <memory>
#include <map>

#include "Bitmap.h"
#include "Command.h"
#include "Resource.h"
#include "GDIBitmap.h"
#include "GameScreen.h"

class GameScreen;
enum GameScreenType;

class Game {
public:
    Game() {};
    ~Game() {};

    bool loadBitmapFromFile(const std::wstring filename, Resource resource);
    void initializeGraphics(HWND window);
    void beginGraphics();
    void drawBitmap(Bitmap bitmap, int x, int y)  const;
    void drawString(const std::wstring text, COLORREF color, int x, int y) const;
    void render(const double interpolation);
    void update(const double deltaTime);
    void endGraphics();
    void freeBitmap(Bitmap bitmap);
    void shutdownGraphics();

    void start();

	std::vector<Command> getCommandsThisFrame();
	void addCommand(Command command);

	void pushGameScreen(GameScreenType gameScreenType);
	void popGameScreen();

    // GDI-related stuff
    HWND window;
    HDC backbufferDC;
    HBITMAP backbufferBitmap;
    HDC bitmapDC;
    HGDIOBJ oldObject;
    // EOF GDI

	std::shared_ptr<Game> game;
	std::vector<std::shared_ptr<GameScreen>> screens;
	std::map<GameScreenType, std::shared_ptr<GameScreen>> gameScreenDictionary;
    std::map<Resource, Bitmap> bitmapDictionary;
    std::map<Resource, std::wstring> fileDictionary;
    std::vector<GDIBitmap> gdiBitmaps;
    std::vector<Bitmap> bitmaps;
	std::vector<Command> commandsThisFrame;
};