#include "img/image.hpp"
#include "util/program_arguments.hpp"

#include <fstream>
#include <gsl/gsl>
#include <iostream>
#include <span>
#include <vector>

int main(int argc, char ** argv) {
  std::span const args_view{argv, gsl::narrow<std::size_t>(argc)};
  std::vector<std::string> const arguments{args_view.begin() + 1, args_view.end()};
  util::program_arguments const prog_args{arguments};
  std::cout << prog_args;

  std::ifstream input{prog_args.input_filename(), std::ios::binary};
  if (!input) {
    std::cerr << "Cannot open file: " << prog_args.input_filename() << '\n';
    std::exit(-1);
  }
  img::image input_image;
  input_image.read(input);
  std::cout << input_image.metadata();

  std::ofstream output{prog_args.output_filename(), std::ios::binary};
  if (!output) {
    std::cerr << "Cannot open file: " << prog_args.output_filename() << '\n';
    std::exit(-2);
  }
  input_image.write(output);
}