#include <array>
#include <cassert>
#include <iostream>
#include <ostream>
#include <span>

namespace {
struct Rgb {
	std::array<std::uint8_t, 3> values{};
};

struct ImageData {
	std::span<Rgb const> data{};
	std::array<std::uint32_t, 2> extent{};
};

std::ostream& operator<<(std::ostream& out, ImageData const& image) {
	assert(image.data.size() == image.extent[0] * image.extent[1]);
	// write header
	out << "P3\n" << image.extent[0] << ' ' << image.extent[1] << "\n255\n";
	// write each row
	for (std::uint32_t row = 0; row < image.extent[1]; ++row) {
		// write each column
		for (std::uint32_t col = 0; col < image.extent[0]; ++col) {
			// compute index
			auto const index = row * image.extent[0] + col;
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
	static constexpr auto extent = std::array{40U, 30U};
	static constexpr auto white_v = Rgb{.values = {0xff, 0xff, 0xff}};
	auto buffer = std::array<Rgb, extent[0] * extent[1]>{};
	std::fill_n(buffer.data(), buffer.size(), white_v);
	auto const image_data = ImageData{.data = buffer, .extent = extent};
	std::cout << image_data;
}
