project(libjson-test C)
add_executable(json-test ./json-test.c)

link_directories(${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(json-test jsonC)
