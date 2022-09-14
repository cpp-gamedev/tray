#pragma once
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>

namespace tray {
template <typename Type, std::size_t Dim>
class Vec;

template <typename T, typename Type, std::size_t Dim>
concept VecOrType = std::same_as<T, Type> || std::convertible_to<T, Vec<Type, Dim>>;

template <typename Type, std::size_t Dim>
class Vec {
	using Storage = std::array<Type, Dim>;

  public:
	using value_type = Type;
	using iterator = typename Storage::iterator;
	using const_iterator = typename Storage::const_iterator;
	static constexpr auto size_v = Dim;

	static constexpr std::size_t size() { return size_v; }

	Vec() = default;

	explicit constexpr Vec(Type const t) {
		for (Type& value : m_values) { value = t; }
	}

	template <std::same_as<Type>... T>
		requires(sizeof...(T) == Dim)
	constexpr Vec(T const... t) : m_values{t...} {}

	constexpr Type& at(std::size_t index) {
		assert(index < Dim);
		return m_values[index];
	}

	constexpr Type const& at(std::size_t index) const {
		assert(index < Dim);
		return m_values[index];
	}

	constexpr Type& operator[](std::size_t index) { return at(index); }
	constexpr Type const& operator[](std::size_t index) const { return at(index); }

	constexpr Type& x() { return at(0); }
	constexpr Type const& x() const { return at(0); }
	constexpr Type& y() requires(Dim > 1) { return at(1); }
	constexpr Type const& y() const requires(Dim > 1) { return at(1); }
	constexpr Type& z() requires(Dim > 2) { return at(2); }
	constexpr Type const& z() const requires(Dim > 2) { return at(2); }

	constexpr Vec& operator-() requires(!std::is_unsigned_v<Type>) {
		for (auto& value : m_values) { value = -value; }
		return *this;
	}

	constexpr Vec& operator+=(Vec const& rhs) {
		for_each(*this, [&rhs](std::size_t i, Type& value) { value += rhs.at(i); });
		return *this;
	}

	constexpr Vec& operator-=(Vec const& rhs) {
		for_each(*this, [&rhs](std::size_t i, Type& value) { value -= rhs.at(i); });
		return *this;
	}

	constexpr Vec& operator*=(Vec const& rhs) {
		for_each(*this, [&rhs](std::size_t i, Type& value) { value *= rhs.at(i); });
		return *this;
	}

	constexpr Vec& operator/=(Vec const& rhs) {
		for_each(*this, [&rhs](std::size_t i, Type& value) { value /= rhs.at(i); });
		return *this;
	}

	constexpr Vec& operator+=(Type const type) {
		for_each(*this, [type](std::size_t, Type& value) { value += type; });
		return *this;
	}

	constexpr Vec& operator-=(Type const type) {
		for_each(*this, [type](std::size_t, Type& value) { value -= type; });
		return *this;
	}

	constexpr Vec& operator*=(Type const type) {
		for_each(*this, [type](std::size_t, Type& value) { value *= type; });
		return *this;
	}

	constexpr Vec& operator/=(Type const type) {
		for_each(*this, [type](std::size_t, Type& value) { value /= type; });
		return *this;
	}

	template <VecOrType<Type, Dim> T>
	friend constexpr Vec operator+(Vec const& a, T const& b) {
		auto ret = a;
		ret += b;
		return ret;
	}

	template <VecOrType<Type, Dim> T>
	friend constexpr Vec operator-(Vec const& a, T const& b) {
		auto ret = a;
		ret -= b;
		return ret;
	}

	template <VecOrType<Type, Dim> T>
	friend constexpr Vec operator*(Vec const& a, T const& b) {
		auto ret = a;
		ret *= b;
		return ret;
	}

	template <VecOrType<Type, Dim> T>
	friend constexpr Vec operator/(Vec const& a, T const& b) {
		auto ret = a;
		ret /= b;
		return ret;
	}

	friend constexpr Vec operator+(Type const& a, Vec const b) {
		auto ret = b;
		ret += a;
		return ret;
	}

	friend constexpr Vec operator*(Type const& a, Vec const b) {
		auto ret = b;
		ret *= a;
		return ret;
	}

	template <typename F, typename T>
	static constexpr void for_each(T&& vec, F&& func) {
		for (std::size_t i = 0; i < Dim; ++i) { func(i, vec.m_values[i]); }
	}

	constexpr iterator begin() { return m_values.begin(); }
	constexpr iterator end() { return m_values.end(); }
	constexpr const_iterator begin() const { return m_values.begin(); }
	constexpr const_iterator end() const { return m_values.end(); }

	bool operator==(Vec const&) const = default;

  private:
	Storage m_values{};
};

template <std::size_t Dim>
constexpr Vec<float, Dim> lerp(Vec<float, Dim> const& a, Vec<float, Dim> const& b, float const t) {
	auto ret = Vec<float, Dim>{};
	Vec<float, Dim>::for_each(ret, [&a, &b, t](std::size_t i, float& value) { value = std::lerp(a[i], b[i], t); });
	return ret;
}

template <typename Type, std::size_t Dim>
constexpr Type dot(Vec<Type, Dim> const& a, Vec<Type, Dim> const& b) {
	auto ret = Type{};
	Vec<Type, Dim>::for_each(a, [&b, &ret](std::size_t i, Type const& value) { ret += value * b[i]; });
	return ret;
}

template <typename Type, std::size_t Dim>
constexpr Vec<Type, Dim> sqr_mag(Vec<Type, Dim> const& vec) {
	return dot(vec, vec);
}

template <typename Type, std::size_t Dim>
Vec<Type, Dim> magnitude(Vec<Type, Dim> const& vec) {
	return std::sqrt(dot(vec, vec));
}

template <std::size_t Dim>
Vec<float, Dim> normalize(Vec<float, Dim> const& in, float const epsilon = 0.001f) {
	auto const mag = magnitude(in);
	if (std::abs(mag) < epsilon) { return {}; }
	return in / mag;
}

using fvec2 = Vec<float, 2>;
using uvec2 = Vec<std::uint32_t, 2>;
using ivec2 = Vec<std::int32_t, 2>;

using fvec3 = Vec<float, 3>;
using uvec3 = Vec<std::uint32_t, 3>;
using ivec3 = Vec<std::int32_t, 3>;

// tests
static_assert(dot(ivec2{-1, 3}, ivec2{2, 4}) == 10);
static_assert(ivec2{-1, 2} + 2 == ivec2{1, 4});
static_assert(2 * ivec2{-1, 2} == ivec2{-2, 4});
static_assert(-ivec2{-1, 2} == ivec2{1, -2});
} // namespace tray
