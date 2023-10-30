#include "pixel.hpp"

#include "normalized_pixel.hpp"
#include "util/binaryio.hpp"

#include <iostream>
#include <span>

namespace img {

  void pixel::read(std::istream & is) {
    color = util::read_binary_array<uint8_t, num_channels>(is);
  }

  void pixel::write(std::ostream & os) {
    util::write_binary_array<uint8_t, num_channels>(os, color);
  }

  namespace {
    uint8_t to_gray_corrected(uint8_t r, uint8_t g, uint8_t b) noexcept {
      auto real_pixel = normalized_pixel{
        {r, g, b}
      };
      real_pixel.intensity_transform();
    const double gray       = real_pixel.to_gray();
    const double gray_gamma = gamma_correction(gray);
      return gray_denormalize(gray_gamma);
    }
  }

  pixel pixel::to_gray() const {
    const auto gray_level = to_gray_corrected(red(), green(), blue());
    return {gray_level, gray_level, gray_level};
  }


}  // namespace img