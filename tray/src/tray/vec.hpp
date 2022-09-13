#pragma once
#include <array>
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
};

using fvec2 = Vec<float, 2>;
using uvec2 = Vec<std::uint32_t, 2>;
using ivec2 = Vec<std::int32_t, 2>;

using fvec3 = Vec<float, 3>;
using uvec3 = Vec<std::uint32_t, 3>;
using ivec3 = Vec<std::int32_t, 3>;
} // namespace tray
