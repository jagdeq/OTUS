add_library(${LIB_NAME} INTERFACE print_ip.hpp)

set_target_properties(${LIB_NAME} 
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(${LIB_NAME}
    INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

if (MSVC)
    target_compile_options(${LIB_NAME} INTERFACE
        /W4
    )
else()
    target_compile_options(${LIB_NAME} INTERFACE
        -Wall -Wextra -pedantic -Werror
    )
endif()
