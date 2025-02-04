cmake_minimum_required(VERSION 3.10)

project(zenoh_image_example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(zenohc REQUIRED)
find_package(zenohcxx REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(pub_image src/pub_image.cpp)
target_link_libraries(pub_image zenohcxx::zenohc ${OpenCV_LIBS})

add_executable(sub_image src/sub_image.cpp)
target_link_libraries(sub_image zenohcxx::zenohc ${OpenCV_LIBS})


add_executable(pub_shm_image src/pub_shm_image.cpp)
target_link_libraries(pub_shm_image zenohc zenohcxx::zenohc ${OpenCV_LIBS})