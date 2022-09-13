#include <tray/image.hpp>
#include <tray/io.hpp>
#include <tray/vec.hpp>
#include <iostream>
#include <span>

using namespace tray;

int main() {
	static constexpr auto extent = uvec2{400U, 300U};
	auto image = Image{extent};
	for (std::uint32_t row = 0; row < image.extent().y(); ++row) {
		auto const ratio = static_cast<float>(row) / static_cast<float>(image.extent().y());
		auto const tint = ratio * static_cast<float>(0xff);
		for (std::uint32_t col = 0; col < image.extent().x(); ++col) {
			auto& rgb = image[{row, col}];
			rgb.x() = 0xff;
			rgb.y() = static_cast<std::uint8_t>(tint);
		}
	}

	io::write(image, "test.ppm");
}
