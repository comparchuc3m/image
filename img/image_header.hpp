#ifndef IMAGE_IMAGE_HEADER_HPP
#define IMAGE_IMAGE_HEADER_HPP

#include <iosfwd>
#include <array>
#include <vector>
#include <cstdint>

namespace img {

  class image_header {
    public:
      image_header() = default;

      void read(std::istream & is);
      void write(std::ostream & os) const;

      [[nodiscard]] int width() const;

      [[nodiscard]] int height() const;

      [[nodiscard]] int planes() const;

      [[nodiscard]] int bit_count() const;

      [[nodiscard]] int compression() const;

      [[nodiscard]] unsigned pixel_start() const;

      [[nodiscard]] unsigned extra_size() const { return pixel_start() - header_size; }

    private:
      static constexpr int header_size = 54;
      std::array<uint8_t, header_size> header_info_{};
  };


}  // namespace img

#endif  // IMAGE_IMAGE_HEADER_HPP
