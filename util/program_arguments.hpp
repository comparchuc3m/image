#ifndef IMAGE_PROGRAM_ARGUMENTS_HPP
#define IMAGE_PROGRAM_ARGUMENTS_HPP

#include <string>
#include <vector>

namespace util {

  enum class image_operation : uint8_t {
    copy,
    histogram,
    grayscale,
  };

  std::string to_string(image_operation op);
  image_operation parse_operation(std::string const & str);
  inline std::ostream & operator<<(std::ostream & os, image_operation op) {
    return os << to_string(op);
  }

  class program_arguments {
    public:
      explicit program_arguments(std::vector<std::string> const & args);

      [[nodiscard]] image_operation operation() const { return operation_; }
      [[nodiscard]] std::string input_filename() const { return input_filename_; }
      [[nodiscard]] std::string output_filename() const { return output_filename_; }

    private:
      image_operation operation_;
      std::string input_filename_;
      std::string output_filename_;
  };

  std::ostream & operator<<(std::ostream & os, program_arguments const & args);

}  // namespace util

#endif  // IMAGE_PROGRAM_ARGUMENTS_HPP
