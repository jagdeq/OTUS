add_library(${LIB_NAME} ip_filter.hpp ip_filter.cpp)

set_target_properties(${LIB_NAME} 
    PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(${LIB_NAME}
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

if (MSVC)
    target_compile_options(${LIB_NAME} PRIVATE
        /W4
    )
else()
    target_compile_options(${LIB_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()
