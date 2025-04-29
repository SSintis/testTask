cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_executable(main src/main.cpp 
                    src/BmpToConsole.cpp
                    src/BmpEditor.cpp)#сюда вписываем все компоненты для компиляции

target_compile_features(main PRIVATE cxx_std_17)
