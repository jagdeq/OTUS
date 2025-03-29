set(HEADRES
    engine.hpp
    gui.hpp
    model.hpp
)

set(SOURCES
    src/engine.cpp
    src/model.cpp
)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})

set_target_properties(${LIB_NAME} 
    PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(${LIB_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
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
