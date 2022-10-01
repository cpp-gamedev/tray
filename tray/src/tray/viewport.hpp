#pragma once
#include <tray/vec.hpp>

namespace tray {
struct Viewport {
	fvec2 extent{1.0f};
	float depth{1.0f};

	static constexpr Viewport make(uvec2 extent, float depth, float scale = 1.0f) {
		auto const ar = static_cast<float>(extent.x()) / static_cast<float>(extent.y());
		return ar > 1.0f ? Viewport{fvec2{scale, scale / ar}, depth} : Viewport{fvec2{scale * ar, scale}, depth};
	}
};
} // namespace tray
