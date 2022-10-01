#pragma once
#include <tray/nvec3.hpp>
#include <span>

namespace tray {
struct DirLight {
	fvec3 intensity{1.0f};
	nvec3 direction{};

	fvec3 diffuse(nvec3 const normal) const {
		auto const coeff = dot(normal.vec(), -direction.vec());
		return std::max(coeff, 0.15f) * intensity;
	}

	static fvec3 combine(std::span<DirLight const> lights, nvec3 const normal) {
		auto ret = fvec3{};
		for (auto const& light : lights) { ret += light.diffuse(normal); }
		return ret;
	}
};
} // namespace tray
