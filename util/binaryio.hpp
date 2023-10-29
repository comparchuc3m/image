#ifndef IMAGE_BINARYIO_HPP
#define IMAGE_BINARYIO_HPP

#include <span>
#include <iostream>

namespace util {

  template <typename T>
    requires(std::is_fundamental_v<T>)
  char * as_writable_buffer(T & value) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    return reinterpret_cast<char *>(&value);
  }

  template <int N>
  char * as_writable_buffer(std::span<std::byte,N> & value) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    return reinterpret_cast<char *>(value.data());
  }

  template <typename T>
    requires(std::is_fundamental_v<T>)
  char const * as_buffer(T const & value) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    return reinterpret_cast<char const *>(&value);
  }

  template <int N>
  char const * as_buffer(std::span<std::byte const,N> const & value) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    return reinterpret_cast<char const *>(value.data());
  }

  template <typename T>
    requires(std::is_fundamental_v<T>)
  T read_binary_value(std::istream & is) {
    T value{};
    is.read(as_writable_buffer(value), sizeof(value));
    return value;
  }

  template <typename T, int N>
    requires(std::is_fundamental_v<T>)
  std::array<T, N> read_binary_array(std::istream & is) {
    std::array<T, N> value{};
    auto view = std::as_writable_bytes(std::span{value});
    is.read(as_writable_buffer<N>(view), view.size());
    return value;
  }

  template <typename T>
    requires(std::is_fundamental_v<T>)
  void write_binary_value(std::ostream & os, T value) {
    os.write(as_buffer(value), sizeof(value));
  }

  template <typename T, int N>
    requires(std::is_fundamental_v<T>)
  void write_binary_array(std::ostream & os, std::array<T, N> const & value) {
    auto view = std::as_bytes(std::span{value});
    os.write(as_buffer<N>(view), view.size());
  }

}  // namespace util

#endif  // IMAGE_BINARYIO_HPP
