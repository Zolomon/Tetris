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

#include "Settings.h"
#include "Bitmap.h"
#include "Command.h"
#include "Resource.h"
#include "GDIBitmap.h"

//class RenderComponent;
//class PhysicsComponent;

class Game {
public:
    Game() {};
    ~Game() {};

    bool LoadBitmapFromFile(const std::wstring filename, Resource resource);
    void InitializeGraphics(HWND window);
    void BeginGraphics();
    void DrawBitmap(Bitmap bitmap, int x, int y)  const;
    void DrawString(const std::wstring text, COLORREF color, int x, int y) const;
    void Render(const double interpolation);
    void Update(const double deltaTime);
    void EndGraphics();
    void FreeBitmap(Bitmap bitmap);
    void ShutdownGraphics();

    void Start();
    void ProcessInput(Command command);

    // GDI-related stuff
    HWND window;
    HDC backbufferDC;
    HBITMAP backbufferBitmap;
    HDC bitmapDC;
    HGDIOBJ oldObject;

    
    // EOF GDI


    //std::vector<std::shared_ptr<Entity>> entities;
    //std::vector<std::shared_ptr<RenderComponent>> renderComponents;
    //std::vector<std::shared_ptr<PhysicsComponent>> physicsComponents;
    //std::vector<std::shared_ptr<>

    std::map<Resource, Bitmap> bitmapDictionary;
    std::map<Resource, std::wstring> fileDictionary;
    std::vector<GDIBitmap> gdiBitmaps;
    std::vector<Bitmap> bitmaps;
    //Bitmap playerBitmap;
    //int score;
private:
};