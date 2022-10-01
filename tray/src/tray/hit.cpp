#include <tray/hit.hpp>
#include <span>

namespace tray {
namespace {
constexpr float smallet_positive_root(std::span<float const, 2> roots) {
	if (roots[0] < 0.0f) { return roots[1]; }
	if (roots[1] < 0.0f) { return roots[0]; }
	return std::min(roots[0], roots[1]);
}
} // namespace

bool Hit::operator()(Ray const& ray, Sphere const& sphere) {
	auto const co = ray.origin - sphere.centre;
	float const b = 2.0f * dot(ray.direction.vec(), co);
	float const c = dot(co, co) - sphere.radius * sphere.radius;
	float const discriminant = b * b - 4 * c;
	if (discriminant < 0.0f) { return false; }

	auto const sqd = std::sqrt(discriminant);
	float const roots[] = {0.5f * (-b - sqd), 0.5f * (-b + sqd)};
	auto const t = smallet_positive_root(roots);
	if (t < 0.0f) { return false; }

	point = ray.at(t);
	normal = point - sphere.centre;
	return true;
}
} // namespace tray
