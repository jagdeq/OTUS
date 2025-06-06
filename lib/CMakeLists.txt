set(LIB_NAME file_analyzer)

set(HEADERS
    inc/consts.hpp
    inc/hash_calculator.hpp
    inc/options.hpp
    inc/analyzer.hpp
) 

set(SOURCES
    src/hash_calculator.cpp
    src/analyzer.cpp
) 

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})

set_target_properties(${LIB_NAME} 
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    # PUBLIC_HEADER
    #     lib/inc/async/async.h
)

find_package(Boost COMPONENTS filesystem REQUIRED)

target_link_libraries(${LIB_NAME}
    PUBLIC
        # cryptopp
        ${Boost_FILESYSTEM_LIBRARY}
)

target_include_directories(${LIB_NAME}
    PUBLIC
        inc
        # usr/include/cryptopp
        ${Boost_FILESYSTEM_INCLUDE}
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

