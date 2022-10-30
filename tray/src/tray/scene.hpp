#pragma once
#include <tray/light.hpp>
#include <tray/renderable.hpp>
#include <tray/rgb.hpp>
#include <vector>

namespace tray {
struct Scene {
	std::vector<DirLight> dir_lights{};
	std::vector<Renderable> renderables{};
	struct {
		fvec3 top{Rgb::from_hex(0x002277).to_f32()};
		fvec3 bottom{Rgb::from_hex(0xffffff).to_f32()};
	} background{};

	fvec3 raycast(Ray const& ray, Renderable const*& lastHit) const;
	fvec3 rndpoint() const;
};
} // namespace tray
