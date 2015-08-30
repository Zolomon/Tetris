#include "Game.h"
#include "Settings.h"
#include <tchar.h>
#include "MainMenuGameScreen.h"
#include "MainGameScreen.h"
#include "GameScreenType.h"

bool Game::LoadBitmapFromFile(const std::wstring filename, Resource resource)
{
	Bitmap bitmap;
	GDIBitmap gdi;
	gdi.handle = (HBITMAP)LoadImage(0, filename.c_str(), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);

	if (gdi.handle == 0)
	{
		return false;
	}

	// Read size
	BITMAP header;
	GetObject(gdi.handle, sizeof(header), &header);
	gdi.width = header.bmWidth;
	gdi.height = header.bmHeight;

	// cache data
	gdiBitmaps.push_back(gdi);
	bitmap.index = gdiBitmaps.size() - 1;
	bitmaps.push_back(bitmap);
	bitmapDictionary[resource] = bitmap;
	fileDictionary[resource] = filename;

	return true;
}

void Game::InitializeGraphics(HWND window)
{
	// Double buffering, borrowed from GDI-provided wrapper in next assignment
	this->window = window;

	HDC hdc = GetDC(this->window);
	backbufferDC = CreateCompatibleDC(hdc);

	RECT windowSize = { Settings::Window::StartPosition.x,
		Settings::Window::StartPosition.y, Settings::Window::Size.x,
		Settings::Window::Size.y };

	backbufferBitmap = CreateCompatibleBitmap(hdc,
		Settings::Window::Size.x, Settings::Window::Size.y);
	// Store old object so that we don't leak.
	oldObject = SelectObject(backbufferDC, backbufferBitmap);

	SetBkMode(backbufferDC, TRANSPARENT);

	bitmapDC = CreateCompatibleDC(hdc);

	// Load assets
	LoadBitmapFromFile(std::wstring(_T("redblock.bmp")), Resource::RedBlock);
	LoadBitmapFromFile(std::wstring(_T("blueblock.bmp")), Resource::BlueBlock);
	LoadBitmapFromFile(std::wstring(_T("background.bmp")), Resource::Background);
	LoadBitmapFromFile(std::wstring(_T("blackblock.bmp")), Resource::BlackBlock);

	//this->player = std::make_shared<Player>(0, 0);
	//player->resource = Resource::PlayerTile;

	// Initialize entities
	//this->entities.push_back(player);
}

void Game::BeginGraphics()
{
	RECT rectangle = { 0, 0, Settings::Window::Size.x, Settings::Window::Size.y };
	FillRect(backbufferDC, &rectangle, (HBRUSH)COLOR_BACKGROUND);
}

void Game::DrawBitmap(Bitmap bitmap, int x, int y) const
{
	const GDIBitmap& gdi = gdiBitmaps.at(bitmap.index);
	SelectObject(bitmapDC, gdi.handle);
	BitBlt(backbufferDC, x, y, gdi.width, gdi.height, bitmapDC,
		0, 0, SRCCOPY);
}

void Game::DrawString(const std::wstring text, COLORREF color, int x, int y) const
{
	SetTextColor(backbufferDC, color);
	TextOut(backbufferDC, x, y, text.c_str(), text.size());
}

void Game::Update(const double deltaTime)
{
	//for (auto& physics : physicsComponents)
	//{
	//    physics->Update(deltaTime);
	//}
	if (screens.size() > 0) {
		screens[screens.size() - 1]->Update(deltaTime);
	}
}

void Game::Render(const double deltaTime)
{
	BeginGraphics();

	if (screens.size() > 0) {
		screens[screens.size() - 1]->Render(deltaTime);
	}

	/*for (auto& render : renderComponents)
	{
		render->Render(*this);
	}*/

	// In case more entities are added.
	/*for (auto& entity : entities) {
		DrawBitmap(bitmapDictionary.at(entity->resource), entity->x, entity->y);
		}*/

		//std::wstring scoreText(_T("Score: "));
		//scoreText += std::to_wstring(score);
		//DrawString(scoreText, RGB(0, 0, 0), 2, 2);
		//DrawString(scoreText, RGB(255, 255, 255), 0, 0);

	EndGraphics();
}

void Game::EndGraphics()
{
	// Blit-block transfer to the main device context
	HDC windowDC = GetDC(window);
	BitBlt(windowDC, 0, 0, Settings::Window::Size.x,
		Settings::Window::Size.y, backbufferDC, 0, 0, SRCCOPY);
	ReleaseDC(window, windowDC);
}

void Game::FreeBitmap(Bitmap bitmap)
{
	// Find the resource, from the bitmap, to free
	auto findResult = std::find_if(std::begin(bitmapDictionary), std::end(bitmapDictionary), [&](const std::pair<Resource, Bitmap>& pair) {
		return pair.second.index == bitmap.index;
	});
	Resource foundKey;
	if (findResult != std::end(bitmapDictionary))
	{
		foundKey = findResult->first;

		// Remove file and bitmap
		bitmapDictionary.erase(foundKey);
		fileDictionary.erase(foundKey);
	}

	// fria minnet som upptas av en bitmap
	if (gdiBitmaps[bitmap.index].handle != 0)
	{
		DeleteObject(gdiBitmaps[bitmap.index].handle);
		gdiBitmaps[bitmap.index].handle = 0;
	}
}

void Game::ShutdownGraphics()
{
	for (auto& bm : bitmaps) {
		FreeBitmap(bm);
	}

	// fria alla resurser som anvönds av grafiksystemet
	DeleteDC(this->bitmapDC);

	DeleteObject(this->backbufferBitmap);
	SelectObject(this->backbufferDC, oldObject);
	DeleteDC(this->backbufferDC);
}

void Game::Start()
{
	/*auto redBlockPhysicsComponent = std::make_shared<PhysicsComponent>(glm::vec2(10.0f, 10.0f), glm::vec2(16.0f));
	auto redBlockRenderComponent = std::make_shared<RenderComponent>(bitmapDictionary[Resource::RedBlock], redBlockPhysicsComponent);*/

	//physicsComponents.push_back(redBlockPhysicsComponent);
	//renderComponents.push_back(redBlockRenderComponent);
	gameScreenDictionary[GameScreenType::MainMenu] = std::make_shared<MainMenuGameScreen>(game);
	gameScreenDictionary[GameScreenType::Play] = std::make_shared<MainGameScreen>(game);
	
	PushGameScreen(GameScreenType::MainMenu);
}

void Game::ProcessInput(Command command)
{

}

std::vector<Command> Game::GetCommandsThisFrame()
{
	auto commands = this->commandsThisFrame;
	commandsThisFrame.clear();
	return commands;
}

void Game::AddCommand(Command command)
{
	commandsThisFrame.push_back(command);
}

void Game::PushGameScreen(GameScreenType gameScreenType)
{
	this->screens.push_back(gameScreenDictionary[gameScreenType]);
}

void Game::PopGameScreen()
{
	this->screens.pop_back();
}





