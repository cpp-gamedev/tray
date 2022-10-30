#include <tray/hit.hpp>
#include <tray/image.hpp>
#include <tray/io.hpp>
#include <tray/scene.hpp>
#include <tray/viewport.hpp>
#include <algorithm>
#include <iostream>
#include <span>

using namespace tray;

namespace {
constexpr fvec3 clamp(fvec3 in, float lo = 0.0f, float hi = 1.0f) {
	in.x() = std::clamp(in.x(), lo, hi);
	in.y() = std::clamp(in.y(), lo, hi);
	in.z() = std::clamp(in.z(), lo, hi);
	return in;
}
} // namespace

int main() {
	static constexpr auto extent = uvec2{400U, 300U};
	static constexpr auto viewport = Viewport::make(extent, 2.0f, 2.0f);
	static constexpr auto origin = fvec3{};

	static constexpr auto horizontal = fvec3{viewport.extent.x(), 0.0f, 0.0f};
	static constexpr auto vertical = fvec3{0.0f, viewport.extent.y(), 0.0f};
	static constexpr auto top_left = origin + 0.5f * (-horizontal + vertical) + fvec3{0.0f, 0.0f, -viewport.depth};

	auto scene = Scene{};
	scene.renderables.push_back(Sphere{.centre = {0.0f, 0.0f, -5.0f}, .radius = 1.0f});
	scene.renderables.push_back({
		Sphere{.centre = {0.5f, -4.0f, -10.0f}, .radius = 5.0f},
		Material{.albedo = {0.2f, 0.8f, 0.7f}},
	});
	scene.dir_lights = {
		DirLight{.intensity = {1.0f, 1.0f, 1.0f}, .direction = fvec3{-1.0f}},
		DirLight{.intensity = {0.5f, 0.3f, 0.3f}, .direction = fvec3{0.0f, 0.0f, -1.0f}},
	};

	auto image = Image{extent};
	Renderable const* ptr = nullptr;
	for (std::uint32_t row = 0; row < image.extent().y(); ++row) {
		auto const yt = static_cast<float>(row) / static_cast<float>(image.extent().y() - 1);
		for (std::uint32_t col = 0; col < image.extent().x(); ++col) {
			auto const xt = static_cast<float>(col) / static_cast<float>(image.extent().x() - 1);
			auto const dir = top_left + xt * horizontal - yt * vertical - origin;
			auto const ray = Ray{origin, dir};
			fvec3 vec(clamp(scene.raycast(ray, ptr)));
			image[{row, col}] = Rgb::from_f32(fvec3(sqrt(vec.x()), sqrt(vec.y()), sqrt(vec.z())));
		}
	}

	io::write(image, "test.ppm");
}
