#include <tray/vec.hpp>
#include <array>
#include <cassert>
#include <iostream>
#include <ostream>
#include <span>

using namespace tray;

namespace {
struct Rgb : Vec<std::uint8_t, 3> {};

struct ImageData {
	std::span<Rgb const> data{};
	uvec2 extent{};
};

std::ostream& operator<<(std::ostream& out, ImageData const& image) {
	assert(image.data.size() == image.extent.x() * image.extent.y());
	// write header
	out << "P3\n" << image.extent.x() << ' ' << image.extent.y() << "\n255\n";
	// write each row
	for (std::uint32_t row = 0; row < image.extent.y(); ++row) {
		// write each column
		for (std::uint32_t col = 0; col < image.extent.x(); ++col) {
			// compute index
			auto const index = row * image.extent.x() + col;
			// obtain corresponding Rgb
			auto const& rgb = image.data[index];
			// write out each channel
			for (auto const channel : rgb.values) { out << static_cast<int>(channel) << ' '; }
		}
		out << '\n';
	}
	return out;
}
} // namespace

int main() {
	static constexpr auto extent = uvec2{40U, 30U};
	static constexpr auto white_v = Rgb{0xff, 0xff, 0xff};
	auto buffer = std::array<Rgb, extent.x() * extent.y()>{};
	std::fill_n(buffer.data(), buffer.size(), white_v);
	auto const image_data = ImageData{.data = buffer, .extent = extent};
	std::cout << image_data;
}
