#include "histogram.hpp"

#include <iostream>

namespace img {

  void histogram::add_color(pixel p) {
    channels[red_channel][p.red()]++;
    channels[green_channel][p.green()]++;
    channels[blue_channel][p.blue()]++;
  }

  void histogram::write(std::ostream & os) const {
    for (auto const value : channels[red_channel]) { os << value << '\n'; }
    for (auto const value : channels[green_channel]) { os << value << '\n'; }
    for (auto const value : channels[blue_channel]) { os << value << '\n'; }
  }

}  // namespace img