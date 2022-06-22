#include <iostream>

#include "Engine/GameFramework/Game.h"
#include "Engine/GameFramework/Components/ColorRectComponent.h"
#include "Engine/Utils/Log.h"
#include "WindowSystem/OpenglWindow.h"

#include "Engine/GameFramework/Objects/Actor.h"
#include "Engine/Resources/ShaderStorage.h"
#include "Engine/Utils/Checks.h"
#include "Engine/Utils/FileSystem.h"
#include "OpenGL/Core/Buffer.h"
#include "OpenGL/Core/IRenderable.h"
#include "OpenGL/Core/Scene.h"


using namespace std;


class GameMock: public Unk::Game
{
public:
	GameMock(ISdlWindow* window):
		Game(window)
	{
	}

	void Init()
	{
		InitInput();
		CreateObjects();
	}
    
	void InitInput()
	{
		InputSystem::Get().Add(SDL_SCANCODE_ESCAPE,
			[this](KeyState state)
			{
				if (state == KeyState::Pressed)
					GetWindow()->Close();
			});
	}
	void CreateObjects()
	{
		CheckMsgReturn(LoadShaders(), "Shaders not loaded");
        
		std::shared_ptr<Scene> mainScene = AddAndSwitchScene<Scene>("Default");
		
		auto shader = ShaderStorage::Self().GetShader("default");
		CheckMsgReturn(shader, "Shader not compiled");

		Unk::Actor& actor = actors.emplace_back();
		Unk::ColorRectComponent* rectComp = actor.Add<Unk::ColorRectComponent>(mainScene.get());
		
		rectComp->GetRenderable().SetShader(shader);

		std::map<float, char> s;
		s.emplace(std::make_pair(1.f, 'c')).first->second;
	}
    
	bool LoadShaders()
	{
		auto& storage = ShaderStorage::Self();
		std::string defaultVertexShader = FileSystem::ReadResource("Shaders/default.vsh");
		std::string defaultFragmentShader = FileSystem::ReadResource("Shaders/default.fsh");
		auto vsh = storage.LoadShaderPart("devault_vertex", ShaderPart::Type::Vertex, defaultVertexShader);
		CheckReturn(vsh, false);
		
		auto fsh = storage.LoadShaderPart("devault_fragment", ShaderPart::Type::Fragment, defaultFragmentShader);
		CheckReturn(fsh, false);
		
		auto shader = storage.LoadShader("default",{vsh, fsh});
		CheckReturn(shader, false);
		
		return true;
	}
	std::vector<Unk::Actor> actors;
};



int main(int argc, char** argv)
{
    Log::ScopedLog("App lifetime");
    
    ISdlWindowParams params;
    params.vsync = true;
    std::shared_ptr<OpenglWindow> Window = std::make_shared<OpenglWindow>(params);

    GameMock game(Window.get());
    game.Init();
    game.Run();

    return 0;
}
