cmake_minimum_required(VERSION 3.20)
project(Untitled)


set(CMAKE_CXX_STANDARD 20)  # Cambia de 17 a 20
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(Untitled main.cpp)


find_package(PostgreSQL REQUIRED)
find_package(libpqxx REQUIRED)


target_link_libraries(Untitled PRIVATE libpqxx::pqxx PostgreSQL::PostgreSQL)