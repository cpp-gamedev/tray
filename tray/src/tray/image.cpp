#include <tray/image.hpp>
#include <cassert>
#include <utility>

namespace tray {
void Image::resize(uvec2 extent) {
	m_data.resize(extent.x() * extent.y());
	m_extent = extent;
}

Rgb const& Image::operator[](Index2D i) const {
	auto const index = i.index(m_extent);
	assert(index < m_data.size());
	return m_data[index];
}

Rgb& Image::operator[](Index2D i) { return const_cast<Rgb&>(std::as_const(*this)[i]); }
} // namespace tray
