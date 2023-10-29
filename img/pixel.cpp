#include "pixel.hpp"

#include <iostream>
#include <span>

#include "util/binaryio.hpp"

namespace img {

  void pixel::read(std::istream & is) {
    color = util::read_binary_array<uint8_t, num_channels>(is);
  }

  void pixel::write(std::ostream & os) {
    util::write_binary_array<uint8_t, num_channels>(os, color);
  }
}  // namespace img