#include "image_header.hpp"

#include "checking.hpp"
#include "util/binaryio.hpp"

#include <gsl/gsl>

namespace img {

  namespace {
    constexpr int pixel_start_offset = 10;
    constexpr int width_offset       = 18;
    constexpr int height_offset      = 22;
    constexpr int planes_offset      = 26;
    constexpr int bit_count_offset   = 28;
    constexpr int compression_offset = 30;

    template <typename T, int N>
    T get_value(std::span<uint8_t const, N> const buffer, int offset) {
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
      gsl::not_null<T const *> const p_value = reinterpret_cast<T const *>(buffer.data() + offset);
      return *p_value;
    }

    template <typename T, int N>
    void set_value(std::span<uint8_t, N> buffer, int offset, T value) {
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
      gsl::not_null<T *> const p_value = reinterpret_cast<T *>(buffer.data() + offset);
      *p_value                         = value;
    }
  }  // namespace

  int image_header::width() const {
    return get_value<int32_t, header_size>(std::span{header_info_}, width_offset);
  }

  int image_header::height() const {
    return get_value<int32_t, header_size>(std::span{header_info_}, height_offset);
  }

  int image_header::planes() const {
    return get_value<int16_t, header_size>(std::span{header_info_}, planes_offset);
  }

  int image_header::bit_count() const {
    return get_value<uint16_t, header_size>(std::span{header_info_}, bit_count_offset);
  }

  int image_header::compression() const {
    return get_value<int32_t, header_size>(std::span{header_info_}, compression_offset);
  }

  unsigned image_header::pixel_start() const {
    return get_value<int32_t, header_size>(std::span{header_info_}, pixel_start_offset);
  }

  void image_header::read(std::istream & is) {
    header_info_ = util::read_binary_array<uint8_t, header_size>(is);
    check_file_error(header_info_[0] == 'B' and header_info_[1] == 'M', file_error_kind::invalid_magic_number);
    check_file_error(pixel_start() >= header_size, file_error_kind::invalid_pixel_start);
  }

  void image_header::write(std::ostream & os) const {
    util::write_binary_array<uint8_t, header_size>(os, header_info_);
  }

}  // namespace img