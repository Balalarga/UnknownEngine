#pragma once

#include <string>
#include <map>
#include <memory>
#include <vector>

#include "OpenGL/Core/ShaderPart.h"

class Shader;


class ShaderStorage
{
public:
	static ShaderStorage& Self();
	static void Destroy();

	std::shared_ptr<ShaderPart> LoadShaderPart(const std::string& tag, ShaderPart::Type type, const std::string& code);
	std::shared_ptr<ShaderPart> GetShaderPart(const std::string& tag);
	bool HasShaderPart(const std::string& tag);

	std::shared_ptr<Shader> LoadShader(const std::string& tag, const std::vector<std::shared_ptr<ShaderPart>>& parts);
	std::shared_ptr<Shader> LoadShader(const std::string& tag, const std::vector<std::string>& parts);
	std::shared_ptr<Shader> GetShader(const std::string& tag);
	bool HasShader(const std::string& tag);


protected:
	ShaderStorage() = default;
	~ShaderStorage() = default;


private:
	std::map<std::string, std::shared_ptr<ShaderPart>> _shaderParts;
	std::map<std::string, std::shared_ptr<Shader>> _shaders;
};
