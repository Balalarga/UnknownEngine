#include "Game.h"

#include <chrono>

#include "Engine/Resources/ShaderStorage.h"
#include "WindowSystem/ISdlWindow.h"


namespace Unk
{


Game::Game(ISdlWindow* window):
	_upsTicks(60),
	_upsTime(1.0/60.0),
	_window(window)
{
	
}

Game::~Game()
{
	ShaderStorage::Destroy();
}

void Game::Run()
{
	using namespace std::chrono;
	
	bool isRunning = true;
	duration<microseconds> frameDuration;
	double updCounter = 0;
	_window->Show();
	while (isRunning)
	{
		high_resolution_clock::time_point frameStart = high_resolution_clock().now();
		_window->PollEvents();
		if (updCounter >= _upsTime)
		{
			Update(_upsTime);
			updCounter -= _upsTime;
		}
		
		_window->RenderFrame();
		isRunning = _window->ShouldClose();
		high_resolution_clock::time_point frameEnd = high_resolution_clock().now();
		frameDuration = duration_cast<duration<microseconds>>(frameEnd - frameStart);
		updCounter += frameDuration.count()/1000.0;
	}
}

void Game::Update(double dt)
{

}

void Game::SetUpdateTicks(unsigned ticks)
{
	_upsTicks = ticks;
	_upsTime = 1.0 / ticks;
}

std::shared_ptr<Scene> Game::GetScene(const std::string& name)
{
	auto it = _scenes.find(name);
	if (it == _scenes.end())
		return nullptr;
	return it->second;
}

bool Game::SwitchScene(const std::string& sceneName)
{
	auto scene = GetScene(sceneName);
	if (!scene)
		return false;
	
	_window->SetScene(scene.get());
	return true;
}

}