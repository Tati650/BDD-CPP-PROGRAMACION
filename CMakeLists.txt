cmake_minimum_required(VERSION 3.20)
project(Untitled)

set(CMAKE_CXX_STANDARD 17)

# Indicar el toolchain de vcpkg
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Buscar libpqxx (usa los cmake files de vcpkg)
find_package(libpqxx CONFIG REQUIRED)

# Crear el ejecutable
add_executable(${PROJECT_NAME} main.cpp)

# Enlazar libpqxx
target_link_libraries(${PROJECT_NAME} PRIVATE pqxx)
