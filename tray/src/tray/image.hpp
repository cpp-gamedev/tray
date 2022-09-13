#pragma once
#include <tray/rgb.hpp>
#include <vector>

namespace tray {
struct Index2D {
	std::uint32_t row{};
	std::uint32_t col{};

	constexpr std::size_t index(uvec2 const extent) { return row * extent.x() + col; }
};

class Image {
  public:
	Image() = default;
	Image(uvec2 extent) { resize(extent); }

	void resize(uvec2 extent);

	Rgb const& operator[](Index2D i) const;
	Rgb& operator[](Index2D i);

	uvec2 extent() const { return m_extent; }

  private:
	std::vector<Rgb> m_data{};
	uvec2 m_extent{};
};
} // namespace tray
