cmake_minimum_required(VERSION 3.30)

project(alce_library
    VERSION 1.0.0.0
    DESCRIPTION "Alce Library is a collection of utils for Anstro Pleuton's programs."
    HOMEPAGE_URL "https://anstropleuton.github.io/alce_library/"
    LANGUAGES CXX
)

option(ALCE_LIBRARY_BUILD_TESTS "Build Alce Library tests" OFF)
option(ALCE_LIBRARY_BUILD_EXAMPLES "Build Alce Library usage examples" OFF)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/alce_library_config.hpp.in" alce_library_config.hpp)

set(ALCE_LIBRARY_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/argument_parser.cpp"
)
set(ALCE_LIBRARY_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/alce_ansi_escape_codes.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/alce_argument_parser.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/alce_container_utilities.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/alce_file_utilities.hpp"
    "${CMAKE_CURRENT_BINARY_DIR}/alce_library_config.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/alce_library.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/alce_string_manipulators.hpp"
)
set(ALCE_LIBRARY_INCLUDE_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_BINARY_DIR}"
)

add_library(alce_library )
target_sources(alce_library PRIVATE ${ALCE_LIBRARY_SOURCES})
target_sources(alce_library PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${ALCE_LIBRARY_INCLUDE_DIRS}
    FILES ${ALCE_LIBRARY_HEADERS}
)
target_compile_features(alce_library PUBLIC cxx_std_23)

if(ALCE_LIBRARY_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(ALCE_LIBRARY_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/alce_library_config_version.cmake"
    COMPATIBILITY AnyNewerVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/alce_library_config_version.cmake"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/alce_library"
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/alce_library.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/alce_library.pc
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/alce_library.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

install(
    TARGETS alce_library
    EXPORT alce_library_targets
    FILE_SET HEADERS
)

install(
    EXPORT alce_library_targets
    NAMESPACE alce_library::
    DESTINATION "${CMAKE_INSTALL_DATADIR}/alce_library"
)
