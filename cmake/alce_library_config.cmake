# alce_library_config.cmake
include(${CMAKE_CURRENT_LIST_DIR}/alce_library_targets.cmake)

install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/alce_library_config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/alce_library_config_version.cmake
    DESTINATION ${CMAKE_INSTALL_DATADIR}/alce_library
)
