cmake_minimum_required(VERSION 3.16)
project(oficina LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(oficina_lib
    src/veiculo.cpp src/carro_combustao.cpp src/carro_eletrico.cpp src/moto.cpp)
target_include_directories(oficina_lib PUBLIC include)
target_compile_options(oficina_lib PRIVATE
    -Wall -Wextra -Wpedantic -Wshadow -Wold-style-cast -Wcast-align
    -Wconversion -Wsign-conversion -Wnon-virtual-dtor -Wdouble-promotion
    -Wformat=2 -Werror)

add_executable(oficina src/main.cpp)
target_link_libraries(oficina PRIVATE oficina_lib)
