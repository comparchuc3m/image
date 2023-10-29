#ifndef IMAGE_PIXEL_HPP
#define IMAGE_PIXEL_HPP

#include <array>
#include <cstdint>
#include <iosfwd>

namespace img {

  class pixel {
    public:
      pixel() = default;

      pixel(uint8_t r, uint8_t g, uint8_t b) : color{r,g,b} {}

      void read(std::istream & is);
      void write(std::ostream & os);

    private:
      static constexpr int num_channels = 3;
      std::array<uint8_t, num_channels> color;
  };

}  // namespace img

#endif  // IMAGE_PIXEL_HPP
