#include "processing.hpp"

#include "img/image.hpp"

#include <fstream>
#include <iostream>
#include <chrono>

void copy(std::istream & is, std::ostream & os) {
  img::image input_image;
  input_image.read(is);
  std::cout << input_image.metadata();
  input_image.write(os);
}

auto grayscale(std::istream & is, std::ostream & os) {
  using namespace std::chrono;
  img::image input_image;
  input_image.read(is);
  std::cout << input_image.metadata();
  auto start = high_resolution_clock::now();
  input_image.to_grayscale();
  auto stop = high_resolution_clock::now();
  auto diff = duration_cast<microseconds>(stop-start);
  std::cout << "Ellapsed: " << diff.count() << " us\n";
  input_image.write(os);
  return diff;
}

void compute_histogram(std::istream & is, std::ostream & os) {
  using namespace std::chrono;
  img::image input_image;
  input_image.read(is);
  std::cout << input_image.metadata();
  auto start = high_resolution_clock::now();
  auto histo = input_image.generate_histogram();
  auto stop = high_resolution_clock::now();
  auto diff = duration_cast<microseconds>(stop-start);
  std::cout << "Ellapsed: " << diff.count() << " us\n";
  histo.write(os);
}

void run_operation(util::program_arguments const & args) {
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
      grayscale(input, output);
      break;
    case util::image_operation::histogram:
      compute_histogram(input, output);
      break;
    default:
      std::cerr << "Unexpected operation\n";
      std::exit(-1);
  }
}
