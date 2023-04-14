cmake_minimum_required(VERSION 3.5)

project(belzebubchr LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(belzebubchr main.cpp belzebubchr.cpp)

install(TARGETS belzebubchr
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

target_link_libraries(${PROJECT_NAME} z)
