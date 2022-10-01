#include <tray/image.hpp>
#include <tray/io.hpp>
#include <tray/ray.hpp>
#include <tray/viewport.hpp>
#include <iostream>
#include <span>

using namespace tray;

int main() {
	static constexpr auto extent = uvec2{400U, 300U};
	static constexpr auto viewport = Viewport::make(extent, 2.0f, 2.0f);
	static constexpr auto origin = fvec3{};

	static constexpr auto horizontal = fvec3{viewport.extent.x(), 0.0f, 0.0f};
	static constexpr auto vertical = fvec3{0.0f, viewport.extent.y(), 0.0f};
	static constexpr auto top_left = origin + 0.5f * (-horizontal + vertical) + fvec3{0.0f, 0.0f, -viewport.depth};

	static constexpr fvec3 gradient[] = {Rgb::from_hex(0xffffff).to_f32(), Rgb::from_hex(0x002277).to_f32()};
	auto image = Image{extent};

	for (std::uint32_t row = 0; row < image.extent().y(); ++row) {
		auto const yt = static_cast<float>(row) / static_cast<float>(image.extent().y() - 1);
		for (std::uint32_t col = 0; col < image.extent().x(); ++col) {
			auto const xt = static_cast<float>(col) / static_cast<float>(image.extent().x() - 1);
			auto const dir = top_left + xt * horizontal - yt * vertical - origin;
			auto const ray = Ray{origin, dir};
			auto const t = 0.5f * (ray.direction.vec().y() + 1.0f);
			image[{row, col}] = Rgb::from_f32(lerp(gradient[0], gradient[1], t));
		}
	}

	io::write(image, "test.ppm");
}
