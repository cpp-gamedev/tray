#include <tray/image.hpp>
#include <tray/io.hpp>
#include <tray/ray.hpp>
#include <tray/vec.hpp>
#include <iostream>
#include <span>

using namespace tray;

int main() {
	static constexpr auto extent = uvec2{400U, 300U};
	static constexpr auto origin = fvec3{0.0f, 0.0f, 0.0f};
	static constexpr auto horizontal = fvec3(extent.x() / 100.0f, 0.0f, 0.0f);
	static constexpr auto vertical = fvec3(0.0f, extent.y() / 100.0f, 0.0f);
	static constexpr auto lower_left = origin - horizontal / 2.0f - vertical / 2.0f - fvec3{0.0f, 0.0f, 1.0f};
	auto image = Image{extent};
	for (std::uint32_t row = 0; row < image.extent().y(); ++row) {
		auto const yt = static_cast<float>(row) / static_cast<float>(image.extent().y());
		for (std::uint32_t col = 0; col < image.extent().x(); ++col) {
			auto const xt = static_cast<float>(col) / static_cast<float>(image.extent().x());
			auto const ray = Ray{origin, lower_left + xt * horizontal + yt * vertical - origin};
			auto const t = 0.5f * (normalize(ray.direction.vec()).y() + 1.0f);
			image[{row, col}] = Rgb::from_f32(Rgb::from_hex(0xff0000).to_f32() * t + (1.0f - t) * Rgb::from_hex(0xffffff).to_f32());
		}
	}

	io::write(image, "test.ppm");
}
