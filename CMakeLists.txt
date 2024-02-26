cmake_minimum_required(VERSION 3.27.8)
project(TimberGame)



set(CMAKE_CXX_STANDARD 23)

find_package(SFML 2.5 COMPONENTS graphics window audio REQUIRED)


add_executable(TimberGame main.cpp)
target_link_libraries(TimberGame sfml-graphics sfml-window sfml-audio)
target_include_directories(TimberGame PRIVATE ${SFML_INCLUDE_DIR})