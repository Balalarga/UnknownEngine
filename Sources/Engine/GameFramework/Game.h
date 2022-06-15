#pragma once
#include <map>
#include <string>
#include <memory>

#include "WindowSystem/ISdlWindow.h"

class Scene;
class ISdlWindow;

namespace Unk
{
	
class Game
{
public:
	Game(ISdlWindow* window);
	virtual ~Game();

	virtual void Run()
	{
		_window->Show();
	}

	template<class T, class... TArgs>
	std::shared_ptr<T> AddScene(const std::string& name, TArgs&& ...args)
	{
		if (auto scene = GetScene(name))
			return scene;
		
		auto ptr = std::make_shared<T>(args...);
		_scenes.emplace(name, ptr);
		return ptr;
	}
	template<class T, class... TArgs>
	std::shared_ptr<T> AddAndSwitchScene(const std::string& name, TArgs&& ...args)
	{
		std::shared_ptr<T> scene = AddScene<T>(name, args...);
		_window->SetScene(scene.get());
		return scene;
	}
	
	std::shared_ptr<Scene> GetScene(const std::string& name);
	bool HasScene(const std::string& name) const { return _scenes.find(name) != _scenes.end(); }
	bool SwitchScene(const std::string& sceneName);

	ISdlWindow* GetWindow() { return _window; }

	
private:
	ISdlWindow* _window;
	
	std::map<std::string, std::shared_ptr<Scene>> _scenes;
};

}