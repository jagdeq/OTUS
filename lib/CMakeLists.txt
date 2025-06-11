set(HEADERS
    inc/consts.hpp
    inc/database.hpp
) 

set(SOURCES
    src/database.cpp
) 

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})

set_target_properties(${LIB_NAME} 
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(${LIB_NAME}
    PUBLIC
        inc
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
