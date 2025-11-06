cmake_minimum_required(VERSION 3.20)
project(Untitled)

set(CMAKE_CXX_STANDARD 17)

# Toolchain de vcpkg
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Buscar libpqxx - versión corregida
find_package(libpqxx CONFIG REQUIRED)

# Crear el ejecutable
add_executable(${PROJECT_NAME} main.cpp)

# Enlazar libpqxx - forma correcta
target_link_libraries(${PROJECT_NAME} PRIVATE libpqxx::pqxx)