#ifndef IMAGE_CHECKING_HPP
#define IMAGE_CHECKING_HPP

#include <string>

namespace img {

  enum class file_error_kind : uint8_t {
    cannot_open,
    cannot_read,
    cannot_read_extra,
    cannot_write,
    invalid_magic_number,
    invalid_planes,
    invlaid_bit_count,
    invalid_compression,
    invalid_pixel_start
  };

  std::string to_string(file_error_kind error);

  void check_file_error(bool pred, file_error_kind error_kind);

}
#endif  // IMAGE_CHECKING_HPP
