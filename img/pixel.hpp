#ifndef IMAGE_PIXEL_HPP
#define IMAGE_PIXEL_HPP

#include <array>
#include <cstdint>
#include <iosfwd>

#include "pixel_util.hpp"

namespace img {

  class pixel {
    public:
      pixel() = default;

      pixel(uint8_t r, uint8_t g, uint8_t b) : color{r,g,b} {}

      [[nodiscard]] long red() const noexcept { return color[red_channel]; }

      [[nodiscard]] long green() const noexcept { return color[green_channel]; }

      [[nodiscard]] long blue() const noexcept { return color[blue_channel]; }

      void read(std::istream & is);
      void write(std::ostream & os);

      [[nodiscard]] pixel to_gray() const;

    private:
      std::array<uint8_t, num_channels> color;
  };

}  // namespace img

#endif  // IMAGE_PIXEL_HPP
