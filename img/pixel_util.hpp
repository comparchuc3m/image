#ifndef IMAGE_PIXEL_UTIL_HPP
#define IMAGE_PIXEL_UTIL_HPP

namespace img {
  static constexpr int num_channels = 3;
  static constexpr int red_channel = 2;
  static constexpr int green_channel = 1;
  static constexpr int blue_channel = 0;

  struct pixel_value {
      uint8_t r_;
      uint8_t g_;
      uint8_t b_;
  };
}
#endif  // IMAGE_PIXEL_UTIL_HPP
