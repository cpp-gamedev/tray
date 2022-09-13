#pragma once
#include <array>
#include <cmath>
#include <cstdint>

namespace tray {
template <typename Type, std::size_t Dim>
struct Vec {
	std::array<Type, Dim> values{};

	constexpr Type& x() { return values[0]; }
	constexpr Type const& x() const { return values[0]; }
	constexpr Type& y() requires(Dim > 1) { return values[1]; }
	constexpr Type const& y() const requires(Dim > 1) { return values[1]; }
	constexpr Type& z() requires(Dim > 2) { return values[2]; }
	constexpr Type const& z() const requires(Dim > 2) { return values[2]; }

	template <typename F, typename T>
	static constexpr void for_each(T&& vec, F&& func) {
		for (std::size_t i = 0; i < Dim; ++i) { func(i, vec.values[i]); }
	}
};

template <std::size_t Dim>
constexpr Vec<float, Dim> lerp(Vec<float, Dim> const& a, Vec<float, Dim> const& b, float const t) {
	auto ret = Vec<float, Dim>{};
	Vec<float, Dim>::for_each(ret, [&a, &b, t](std::size_t i, float& value) { value = std::lerp(a.values[i], b.values[i], t); });
	return ret;
}

using fvec2 = Vec<float, 2>;
using uvec2 = Vec<std::uint32_t, 2>;
using ivec2 = Vec<std::int32_t, 2>;

using fvec3 = Vec<float, 3>;
using uvec3 = Vec<std::uint32_t, 3>;
using ivec3 = Vec<std::int32_t, 3>;
} // namespace tray
