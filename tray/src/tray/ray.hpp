#pragma once
#include <tray/nvec3.hpp>

namespace tray {
struct Ray {
	fvec3 origin{};
	nvec3 direction{};

	fvec3 at(float const t) const { return origin + t * direction.vec(); }
};
} // namespace tray
