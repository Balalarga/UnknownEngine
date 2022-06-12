#include "ShaderStorage.h"

#include "OpenGL/Core/Shader.h"
#include "OpenGL/Core/ShaderPart.h"


ShaderStorage& ShaderStorage::Self()
{
	static ShaderStorage storage;
	return storage;
}

void ShaderStorage::Destroy()
{
	Self()._shaders.clear();
	Self()._shaderParts.clear();
}

std::shared_ptr<ShaderPart> ShaderStorage::LoadShaderPart(const std::string& tag, ShaderPart::Type type, const std::string& code)
{
	if (auto existingPart = GetShaderPart(tag))
		return existingPart;

	std::shared_ptr<ShaderPart> part = std::make_shared<ShaderPart>(type, code);
	
	if (!part->Compile())
		return nullptr;
	
	_shaderParts.emplace(tag, part);
	return part;
}

bool ShaderStorage::HasShaderPart(const std::string& tag)
{
	return GetShaderPart(tag) != nullptr;
}

std::shared_ptr<Shader> ShaderStorage::LoadShader(const std::string& tag, const std::vector<std::shared_ptr<ShaderPart>>& parts)
{
	if (auto existingShader = GetShader(tag))
		return existingShader;

	std::shared_ptr<Shader> shader = std::make_shared<Shader>(parts);
	
	if (!shader->Compile())
		return nullptr;
	
	_shaders.emplace(tag, shader);
	return shader;
}

std::shared_ptr<Shader> ShaderStorage::LoadShader(const std::string& tag, const std::vector<std::string>& partNames)
{
	if (auto existingShader = GetShader(tag))
		return existingShader;
	
	std::vector<std::shared_ptr<ShaderPart>> parts;
	for (auto& i: partNames)
	{
		if (auto part = GetShaderPart(i))
			parts.push_back(part);
		else
			return nullptr;
	}
	return LoadShader(tag, parts);
}

std::shared_ptr<Shader> ShaderStorage::GetShader(const std::string& tag)
{
	auto it = _shaders.find(tag);
	if (it != _shaders.end())
		return it->second;
	
	return nullptr;
}

bool ShaderStorage::HasShader(const std::string& tag)
{
	return GetShader(tag) != nullptr;
}

std::shared_ptr<ShaderPart> ShaderStorage::GetShaderPart(const std::string& tag)
{
	auto it = _shaderParts.find(tag);
	if (it != _shaderParts.end())
		return it->second;
	
	return nullptr;
}
