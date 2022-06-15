#pragma once

#include "Engine/GameFramework/Game.h"
#include "Engine/Resources/ShaderStorage.h"
#include "Engine/Utils/Checks.h"
#include "Engine/Utils/FileSystem.h"
#include "OpenGL/Core/Buffer.h"
#include "OpenGL/Core/IRenderable.h"
#include "OpenGL/Core/Scene.h"


class GameMock: public Game
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

		struct Vertex
		{
			glm::fvec3 pos;
			glm::fvec4 color;
		};
		std::vector<Vertex> triangle
		{
	            {glm::fvec3{-0.2f, -0.4f, 0.f}, glm::fvec4{1.f, 0.f, 0.f, 1.f}},
				{glm::fvec3{-0.2f,  0.4f, 0.f}, glm::fvec4{0.f, 1.f, 0.f, 1.f}},
				{glm::fvec3{ 0.3f,  0.0f, 0.f}, glm::fvec4{0.f, 0.f, 1.f, 1.f}},
			};
		Buffer buffer(DataPtr(triangle), BufferLayout().Float(3).Float(4));

		auto& Obj1 = mainScene->AddObject(new IRenderable(buffer));
		auto shader = ShaderStorage::Self().GetShader("default");

		CheckMsgReturn(shader, "Shader not compiled");

		Obj1.SetShader(shader);
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
};
