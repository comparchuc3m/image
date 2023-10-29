#include "image_metadata.hpp"

#include "image_header.hpp"
#include "checking.hpp"
#include "util/binaryio.hpp"

#include <gsl/gsl>

namespace img {

  void image_metadata::read(std::istream & is) {
    using enum img::file_error_kind;

    header_.read(is);

    pixel_start_ = header_.pixel_start();
    width_ = header_.width();
    height_ = header_.height();
    planes_ = header_.planes();
    bit_count_ = header_.bit_count();
    compression_ = header_.compression();
    extra_size_ = header_.extra_size();

    check_file_error(planes_ == 1, invalid_planes);
    check_file_error(bit_count_ == default_bit_count, invlaid_bit_count);
    check_file_error(compression_ == 0, invalid_compression);

    extra_header_.resize(extra_size_);
    is.read(extra_header_.data(), extra_size_);
    check_file_error(static_cast<bool>(is), cannot_read_extra);
  }

  void image_metadata::write(std::ostream & os) const {
    header_.write(os);
    os.write(extra_header_.data(), std::ssize(extra_header_));
  }

  std::ostream & operator<<(std::ostream & os, image_metadata const & meta) {
    os << "Pixel start: " << meta.pixel_start_ << '\n';
    os << "Width: " << meta.width_ << '\n';
    os << "Height: " << meta.height_ << '\n';
    os << "Planes: " << meta.planes_ << '\n';
    os << "Bit count: " << meta.bit_count_ << '\n';
    os << "Compression: " << meta.compression_ << '\n';
    return os;
  }


}  // namespace img