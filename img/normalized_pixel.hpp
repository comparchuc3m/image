#ifndef IMAGE_NORMALIZED_PIXEL_HPP
#define IMAGE_NORMALIZED_PIXEL_HPP

#include <cstdint>
#include <array>

#include "pixel_util.hpp"

namespace img {

  static constexpr double intensity_max_value = 255.0;

  class normalized_pixel {
    public:
      normalized_pixel(pixel_value color) : color{color.b_ / intensity_max_value,
                color.g_ / intensity_max_value,
                color.r_ / intensity_max_value} { }

      [[nodiscard]] double red() const noexcept { return color[red_channel]; }

      [[nodiscard]] double green() const noexcept { return color[green_channel]; }

      [[nodiscard]] double blue() const noexcept { return color[blue_channel]; }

      void intensity_transform() noexcept;

      [[nodiscard]] double to_gray() const noexcept;

    private:
      std::array<double, num_channels> color{};
  };

  double gamma_correction(double g) noexcept;
  uint8_t gray_denormalize(double g) noexcept;

}  // namespace img

#endif  // IMAGE_NORMALIZED_PIXEL_HPP
