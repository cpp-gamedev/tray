#include <tray/scene.hpp>
#include <random>

namespace tray {
fvec3 Scene::raycast(Ray const& ray, Renderable const*& lastHit) const {
	struct {
		Renderable const* renderable{};
		Hit hit{};
	} nearest{};
	auto hit = Hit{};
	for (auto const& renderable : renderables) {
		if (renderable.hit(hit, ray) && (!nearest.renderable || hit.t < nearest.hit.t) && lastHit != &renderable) { nearest = {&renderable, hit}; }
	}
	if (!nearest.renderable) {
		auto const t = 0.5f * (ray.direction.vec().y() + 1.0f);
		return (1.0f - t) * fvec3(1.0f, 1.0f, 1.0f) + t * fvec3(0.5f, 0.7f, 1.0f); //lerp(background.bottom, background.top, t);
	}

	const fvec3 target = hit.point + hit.normal + rndpoint();
	return 0.5f * raycast(Ray{hit.point, target - hit.point}, nearest.renderable) * DirLight::combine(dir_lights, nearest.hit.normal) *
		   nearest.renderable->material.albedo;
}

fvec3 Scene::rndpoint() const {
	fvec3 point;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	do {
		point = 2.0f * fvec3(dist(gen), dist(gen), dist(gen)) - fvec3(1.0f, 1.0f, 1.0f);
	} while (magnitude(point) >= 1.0f);

	return point;
}
} // namespace tray
