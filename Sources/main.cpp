#include <iostream>

#include "Engine/GameFramework/Game.h"
#include "Engine/GameFramework/Components/ColorRectComponent.h"
#include "Engine/GameFramework/Objects/Actor.h"
#include "Engine/Resources/ShaderStorage.h"
#include "Engine/Utils/Checks.h"
#include "Engine/Utils/FileSystem.h"
#include "Engine/Utils/Log.h"
#include "OpenGL/Core/Scene.h"
#include "WindowSystem/OpenglWindow.h"


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

		std::shared_ptr<Shader> shader = ShaderStorage::Self().GetShader("default");
		CheckMsgReturn(shader, "Shader not compiled")

		Unk::Actor& actor = *actors.emplace_back(std::make_unique<Unk::Actor>());
		Unk::ColorRectComponent* rectComp = actor.Add<Unk::ColorRectComponent>(mainScene.get());
		rectComp->GetRenderable().Move({0.5, 0, 0});
		rectComp->GetRenderable().ScaleTo({0.5, 0.5, 1.0});
		rectComp->GetRenderable().Rotate({0, 0, 45});
		rectComp->SetColor({0.5, 0.2, 0.2, 1.0});
		rectComp->GetRenderable().SetShader(shader.get());
	}
    
	bool LoadShaders()
	{
		ShaderStorage& storage = ShaderStorage::Self();
		std::string defaultVertexShader = FileSystem::ReadResource("Shaders/default.vsh");
		std::shared_ptr<ShaderPart> vsh = storage.LoadShaderPart("devault_vertex",
			ShaderPart::Type::Vertex,
			defaultVertexShader);
		
		CheckReturn(vsh, false)

		std::string defaultFragmentShader = FileSystem::ReadResource("Shaders/default.fsh");
		std::shared_ptr<ShaderPart> fsh = storage.LoadShaderPart("devault_fragment",
			ShaderPart::Type::Fragment,
			defaultFragmentShader);
		
		CheckReturn(fsh, false)

		std::shared_ptr<Shader> shader = storage.LoadShader("default", vsh, fsh);
		CheckReturn(shader, false)
		
		return true;
	}
	std::vector<std::unique_ptr<Unk::Actor>> actors;
};


int main(int, char**)
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
