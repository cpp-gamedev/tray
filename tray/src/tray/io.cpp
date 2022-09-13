#include <tray/io.hpp>
#include <fstream>

namespace tray {
std::ostream& operator<<(std::ostream& out, Image const& image) {
	// write header
	out << "P3\n" << image.extent().x() << ' ' << image.extent().y() << "\n255\n";
	// write each row
	for (std::uint32_t row = 0; row < image.extent().y(); ++row) {
		// write each column
		for (std::uint32_t col = 0; col < image.extent().x(); ++col) {
			// obtain corresponding Rgb
			auto const& rgb = image[{row, col}];
			// write out each channel
			for (auto const channel : rgb.values) { out << static_cast<int>(channel) << ' '; }
		}
		out << '\n';
	}
	return out;
}

bool io::write(Image const& image, char const* path) {
	if (auto file = std::ofstream(path)) { return static_cast<bool>(file << image); }
	return false;
}
} // namespace tray
