add_executable(imgtool imgtool.cpp)
target_link_libraries(imgtool PRIVATE
        util img Microsoft.GSL::GSL)