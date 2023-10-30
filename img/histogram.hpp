#ifndef IMAGE_HISTOGRAM_HPP
#define IMAGE_HISTOGRAM_HPP

#include "pixel.hpp"

#include <vector>

namespace img {

  class histogram {
    public:
      histogram() = default;

      void add_color(pixel p);

      void add_red(uint8_t r) { channels[red_channel][r]++; }

      void add_green(uint8_t g) { channels[green_channel][g]++; }

      void add_blue(uint8_t b) { channels[blue_channel][b]++; }

      [[nodiscard]] int get_red_frequency(uint8_t v) const { return channels[red_channel][v]; }

      [[nodiscard]] int get_green_frequency(uint8_t v) const { return channels[green_channel][v]; }

      [[nodiscard]] int get_blue_frequency(uint8_t v) const { return channels[blue_channel][v]; }

      void write(std::ostream & os) const;

    private:
      static constexpr int num_levels          = 256;
      std::array<std::vector<int>, 3> channels = {
        std::vector<int>(num_levels),
        std::vector<int>(num_levels),
        std::vector<int>(num_levels),
      };
  };

}  // namespace img

#endif  // IMAGE_HISTOGRAM_HPP
