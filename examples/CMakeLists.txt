set(ALCE_LIBRARY_EXAMPLES
    "sm/to_string"
    "cu/boundless_containers"
    "cu/enumerated_array"
    "cu/arithmetics"
    "sm/arithmetics"
)

function(add_example source executable)
    add_executable(${executable} ${source})
    target_link_libraries(${executable} alce_library)
endfunction()

foreach(example ${ALCE_LIBRARY_EXAMPLES})
    set(example_source "${CMAKE_CURRENT_SOURCE_DIR}/${example}.cpp")
    string(REPLACE "/" "_" example_executable alce_library_${example})
    add_example(${example_source} ${example_executable})
endforeach()
