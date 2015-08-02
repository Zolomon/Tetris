#pragma once

#include <Windows.h>
#include <algorithm>
#include <iterator>
#include <tchar.h>
#include <cassert>
#include <sstream>
#include <vector>
#include <memory>
#include <map>

#include "Bitmap.h"


class Game {
public:
	Game() {};
	~Game() {};

	void InitializeGraphics(HWND window);
	void BeginGraphics();
	void DrawBitmap(Bitmap bitmap, int x, int y)  const;
	void DrawString(const std::wstring text, COLORREF color, int x, int y) const;
	void DrawLevel() const;
	void Render(const double interpolation);
	void EndGraphics();
	void FreeBitmap(Bitmap bitmap);
	void ShutdownGraphics();

	void Start();
	void MovePlayer(Command command);
	void ProcessInput(Command command);
	void CheckWinningCondition();
	void AddLevel(std::shared_ptr<Level> level);

	// GDI-related stuff
	HWND window;
	int windowWidth;
	int windowHeight;

	HDC backbufferDC;
	HBITMAP backbufferBitmap;

	HDC bitmapDC;

	struct GDIBitmap
	{
		HBITMAP handle;
		int width;
		int height;

		GDIBitmap()
			: handle(0)
		{
		}
	};
	// EOF GDI

	
	std::vector<std::shared_ptr<Entity>> entities;
	std::map<Resource, Bitmap> bitmapDictionary;
	std::map<Resource, std::wstring> fileDictionary;
	std::vector<GDIBitmap> gdiBitmaps;
	std::vector<Bitmap> bitmaps;
	Bitmap playerBitmap;
	int score;
	HGDIOBJ oldObject;
private:
};