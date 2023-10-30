add_library(img
        checking.cpp
        pixel.cpp
        normalized_pixel.cpp
        image_header.cpp
        image_metadata.cpp
        image.cpp
        histogram.cpp)

target_link_libraries(img PRIVATE Microsoft.GSL::GSL)