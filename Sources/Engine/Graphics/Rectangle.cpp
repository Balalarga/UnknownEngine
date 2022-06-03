#include "Rectangle.h"

#include <array>


struct RectangleVertex
{
	glm::fvec3 pos;
	glm::fvec4 color = {1.f, 1.f, 1.f, 1.f};
};


Rectangle::Rectangle(const glm::fvec3& pos, const glm::fvec2& size)
{
	static BufferLayout layout = BufferLayout().Float(3).Float(4);
	std::array data{
		RectangleVertex({pos.x - size.x/2.f, pos.y - size.y/2.f, pos.z}),
		RectangleVertex({pos.x - size.x/2.f, pos.y + size.y/2.f, pos.z}),
		RectangleVertex({pos.x + size.x/2.f, pos.y + size.y/2.f, pos.z}),
		RectangleVertex({pos.x + size.x/2.f, pos.y - size.y/2.f, pos.z})
	};
	_buffer.Layout = layout;
	_buffer.Data = DataPtr(&data[0], data.size(), sizeof(data[0]));
	Setup(_buffer);
}
