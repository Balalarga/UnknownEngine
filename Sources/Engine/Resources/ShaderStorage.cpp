#include "ShaderStorage.h"


ShaderStorage& ShaderStorage::Self()
{
	static ShaderStorage storage;
	return storage;
}
