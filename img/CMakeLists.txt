add_library(img checking.cpp pixel.cpp image_header.cpp image_metadata.cpp image.cpp)
target_link_libraries(img PRIVATE Microsoft.GSL::GSL)