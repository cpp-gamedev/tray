#pragma once
#include <tray/image.hpp>
#include <ostream>

namespace tray {
std::ostream& operator<<(std::ostream& out, Image const& image);

namespace io {
bool write(Image const& image, char const* path);
}
} // namespace tray
