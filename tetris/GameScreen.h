#pragma once
#include "Game.h"
#include "Application.h"
#include <chrono>

class Game;
class Application;

class GameScreen
{
public:
	GameScreen(std::shared_ptr<Game> game, std::shared_ptr<Application> app) : game(game), app(app)
	{
		
	}

	virtual ~GameScreen()
	{
	}

	/*virtual void OnLoad() = 0;
	virtual void Loading() = 0;
	virtual void OnLoaded() = 0;*/
	virtual void Update(const double deltaTime) = 0;
	virtual void Render(const double interpolation) = 0; 
	/*virtual void OnUnloading() = 0;
	virtual void Unloading() = 0;
	virtual void OnUnloaded() = 0;*/

protected:
	std::shared_ptr<Game> game;
	std::shared_ptr<Application> app;
	std::chrono::duration<double> startTime;
	std::chrono::duration<double> duration;
	bool isFinishedLoading;

};




