set(LIB_NAME logger)

set(HEADERS
    aliases.hpp    
    base_logger.hpp
    console_logger.hpp
    file_logger.hpp
)

set(SOURCES
    console_logger.cpp
    file_logger.cpp
)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})

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
