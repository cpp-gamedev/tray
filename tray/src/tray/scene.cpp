#include <tray/scene.hpp>

namespace tray {
fvec3 Scene::raycast(Ray const& ray) const {
	struct {
		Renderable const* renderable{};
		Hit hit{};
	} nearest{};
	auto hit = Hit{};
	for (auto const& renderable : renderables) {
		if (renderable.hit(hit, ray) && (!nearest.renderable || hit.t < nearest.hit.t)) { nearest = {&renderable, hit}; }
	}
	if (!nearest.renderable) {
		auto const t = 0.5f * (ray.direction.vec().y() + 1.0f);
		return lerp(background.bottom, background.top, t);
	}
	return DirLight::combine(dir_lights, nearest.hit.normal) * nearest.renderable->material.albedo;
}
} // namespace tray
