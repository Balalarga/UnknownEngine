#include "Scene.h"

std::set<Shader*> Scene::GetShaders() const
{
	std::set<Shader*> shaders;
	for (auto& obj: _renderObjects)
		if (obj->GetShader())
			shaders.emplace(obj->GetShader());
	return shaders;
}
