#pragma once
#include <tray/hit.hpp>
#include <tray/material.hpp>
#include <memory>

#include "scene.hpp"

namespace tray {
template <typename T>
concept Hittable = requires(T const& t, Ray const& ray) {
	Hit{}(ray, t);
};

class Renderable {
  public:
	template <Hittable T>
	Renderable(T t, Material material = {}) : material{material}, m_model{std::make_unique<Model<T>>(std::move(t))} {}

	bool hit(Hit& out, Ray const& ray) const { return m_model->hit(out, ray); }

	Material material{};

  private:
	struct Base {
		virtual ~Base() = default;
		virtual bool hit(Hit& out, Ray const& ray) const = 0;
	};

	template <Hittable T>
	struct Model final : Base {
		T t;
		Model(T&& t) : t{std::move(t)} {}
		bool hit(Hit& out, Ray const& ray) const override final { return out(ray, t); }
	};

	std::unique_ptr<Base> m_model{};
};
} // namespace tray
