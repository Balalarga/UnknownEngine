#pragma once


enum class ShaderType
{
	Vertex, Fragment, Geometry
};


class ShaderStorage
{
public:
	static ShaderStorage& Self();

	void LoadShader();
	

protected:
	ShaderStorage() = default;
	~ShaderStorage() = default;
};
