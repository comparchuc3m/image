#include "processing.hpp"
#include "img/image.hpp"
#include <fstream>
#include <iostream>

void copy(std::istream & is, std::ostream & os) {
  img::image input_image;
  input_image.read(is);
  std::cout << input_image.metadata();
  input_image.write(os);
}

void grayscale(std::istream & is, std::ostream & os) {
  img::image input_image;
  input_image.read(is);
  std::cout << input_image.metadata();
  input_image.to_grayscale();
  input_image.write(os);
}

void run_operation(util::program_arguments const &  args) {
  std::ifstream input{args.input_filename(), std::ios::binary};
  if (!input) {
    std::cerr << "Cannot open file: " << args.input_filename() << '\n';
    std::exit(-1);
  }
  std::ofstream output{args.output_filename(), std::ios::binary};
  if (!output) {
    std::cerr << "Cannot open file: " << args.output_filename() << '\n';
    std::exit(-2);
  }

  switch (args.operation()) {
    case util::image_operation::copy:
      copy(input, output);
      break;
    case util::image_operation::grayscale:
      grayscale(input,output);
      break;
    case util::image_operation::histogram:
    case util::image_operation::gausss:
    default:
      std::cerr << "Unexpected operation\n";
      std::exit(-1);
  }
}

