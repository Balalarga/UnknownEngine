#include "Game.h"

#include "Engine/Resources/ShaderStorage.h"
#include "WindowSystem/ISdlWindow.h"


namespace Unk
{
	
Game::Game(ISdlWindow* window):
	_window(window)
{
	
}

Game::~Game()
{
	ShaderStorage::Destroy();
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