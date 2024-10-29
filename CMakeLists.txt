cmake_minimum_required(VERSION 3.30)

project(AlceLibrary
    VERSION 1.0.0.0
    DESCRIPTION "Alce Library is a collection of utils for Anstro Pleuton's programs."
    HOMEPAGE_URL "https://anstropleuton.github.io/alce-library/"
    LANGUAGES CXX
)

option(BUILD_SHARED_LIBS "Build Alce Library as shared library" OFF)
option(BUILD_TESTS "Build Alce Library tests" OFF)
option(BUILD_EXAMPLES "Build Alce Library usage examples" OFF)

set(AlceLibrary_gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(AlceLibrary_msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/alce_library_config.hpp.in" alce_library_config.hpp)

add_library(AlceLibrary_compiler_flags INTERFACE)
target_include_directories(AlceLibrary_compiler_flags INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}")
target_compile_features(AlceLibrary_compiler_flags INTERFACE cxx_std_23)

set(AlceLibrary_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/argument_parser.cpp")

add_library(alce_library ${AlceLibrary_SOURCES})
target_link_libraries(alce_library PUBLIC AlceLibrary_compiler_flags)
target_compile_options(alce_library PRIVATE
    $<${AlceLibrary_gcc_like_cxx}:-Wall;-Wextra;-Wshadow;-Wformat=2>
    $<${AlceLibrary_msvc_cxx}:-W3> # I don't know what I am doing with MSVC
)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
