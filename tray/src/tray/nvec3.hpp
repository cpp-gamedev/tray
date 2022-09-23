#pragma once
#include <tray/vec.hpp>

namespace tray {
class nvec3 {
  public:
	nvec3() = default;
	nvec3(fvec3 const vec) : m_vec{normalize(vec)} {}

	fvec3 const& vec() const { return m_vec; }
	operator fvec3 const&() const { return vec(); }

  private:
	fvec3 m_vec{forward_v<>};
};
} // namespace tray
