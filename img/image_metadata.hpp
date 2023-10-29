#ifndef IMAGE_IMAGE_METADATA_HPP
#define IMAGE_IMAGE_METADATA_HPP

#include "image_header.hpp"

#include <array>
#include <cstdint>
#include <iosfwd>
#include <vector>

namespace img {

  class image_metadata {
    public:
      image_metadata() = default;

      [[nodiscard]] int width() const { return width_; }
      [[nodiscard]] int height() const { return height_; }

      void read(std::istream & is);
      void write(std::ostream & os) const;

      friend std::ostream & operator<<(std::ostream & os, image_metadata const & meta);

    private:

      static constexpr int default_bit_count = 24;

      unsigned pixel_start_ = 0;
      int width_ = 0;
      int height_ = 0;
      int planes_ = 1;
      int bit_count_ = default_bit_count;
      int compression_ = 0;

      unsigned extra_size_ = 0;

      image_header header_;
      std::vector<char> extra_header_{};
  };

}  // namespace img

#endif  // IMAGE_IMAGE_METADATA_HPP
