#include <tray/image.hpp>
#include <tray/io.hpp>
#include <tray/vec.hpp>
#include <iostream>
#include <span>

using namespace tray;

int main() {
	static constexpr auto extent = uvec2{400U, 300U};
	static constexpr auto top = std::array{Rgb::from_hex(0xff0000).to_f32(), Rgb::from_hex(0x00ff00).to_f32()};
	static constexpr auto bottom = std::array{Rgb::from_hex(0x0000ff).to_f32(), Rgb::from_hex(0xff00ff).to_f32()};
	auto image = Image{extent};
	for (std::uint32_t row = 0; row < image.extent().y(); ++row) {
		auto const yt = static_cast<float>(row) / static_cast<float>(image.extent().y());
		auto const range = std::array{lerp(top[0], bottom[0], yt), lerp(top[1], bottom[1], yt)};
		for (std::uint32_t col = 0; col < image.extent().x(); ++col) {
			auto const xt = static_cast<float>(col) / static_cast<float>(image.extent().x());
			image[{row, col}] = Rgb::from_f32(lerp(range[0], range[1], xt));
		}
	}

	io::write(image, "test.ppm");
}
