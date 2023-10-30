#include "normalized_pixel.hpp"

#include <cmath>

namespace img {

  namespace {
    constexpr double intensity_divisor1 = 12.92;
    constexpr double intensity_divisor2 = 1.055;
    constexpr double intensity_delta    = 0.055;
    constexpr double intensity_exponent = 2.4;
  }  // namespace

  void normalized_pixel::intensity_transform() noexcept {
    constexpr double intensity_threshold = 0.04045;
    for (auto & component : color) {
      if (component <= intensity_threshold) {
        component /= intensity_divisor1;
      } else {
        component =
            std::pow((component + intensity_delta) / intensity_divisor2, intensity_exponent);
      }
    }
  }

  double normalized_pixel::to_gray() const noexcept {
    constexpr double red_coefficient   = 0.2126;
    constexpr double green_coefficient = 0.7152;
    constexpr double blue_coefficient  = 0.0722;
    return red_coefficient * red() + green_coefficient * green() + blue_coefficient * blue();
  }

  double gamma_correction(double g) noexcept {
    constexpr double intensity_expornent_inv = 1.0 / intensity_exponent;
    constexpr double gamma_threshold         = 0.003108;
    if (g <= gamma_threshold) { return intensity_divisor1 * g; }
    return intensity_divisor2 * std::pow(g, intensity_expornent_inv) - intensity_delta;
  }

  uint8_t gray_denormalize(double g) noexcept {
    return static_cast<uint8_t>(g * intensity_max_value);
  }

}  // namespace img