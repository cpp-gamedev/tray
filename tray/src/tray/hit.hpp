#pragma once
#include <tray/nvec3.hpp>
#include <tray/ray.hpp>
#include <tray/sphere.hpp>

namespace tray {
struct Hit {
	fvec3 point{};
	nvec3 normal{};
	float t{};

	bool operator()(Ray const& ray, Sphere const& sphere);
};
} // namespace tray
