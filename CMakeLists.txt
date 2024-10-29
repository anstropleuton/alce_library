cmake_minimum_required(VERSION 3.30)

project(AlceLibrary
    VERSION 1.0.0.0
    DESCRIPTION "Alce Library is a collection of utils for Anstro Pleuton's programs."
    HOMEPAGE_URL "https://anstropleuton.github.io/alce_library/"
    LANGUAGES CXX
)

option(BUILD_SHARED_LIBS "Build Alce Library as shared library" OFF)
option(BUILD_TESTS "Build Alce Library tests" OFF)
option(BUILD_EXAMPLES "Build Alce Library usage examples" OFF)

set(ALCE_LIBRARY_IS_GCC_LIKE_CXX "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(ALCE_LIBRARY_IS_MSVC_CXX "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/alce_library_config.hpp.in" alce_library_config.hpp)

set(ALCE_LIBRARY_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/argument_parser.cpp"
)
set(ALCE_LIBRARY_INCLUDES_DIRECTORIES
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_BINARY_DIR}"
)

add_library(alce_library ${ALCE_LIBRARY_SOURCES})
target_include_directories(alce_library PUBLIC ${ALCE_LIBRARY_INCLUDES_DIRECTORIES})
target_compile_features(alce_library PUBLIC cxx_std_23)
target_compile_options(alce_library PRIVATE
    $<${ALCE_LIBRARY_IS_GCC_LIKE_CXX}:-Wall;-Wextra;-Wshadow;-Wformat=2>
    $<${ALCE_LIBRARY_IS_MSVC_CXX}:-W3> # I don't know what I am doing with MSVC
)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
