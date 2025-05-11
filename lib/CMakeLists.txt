set(LIB_NAME async)

set(HEADERS
    inc/async/async.h
    inc/aliases.hpp    
    inc/analyzer.hpp    
    inc/async_interface.hpp    
    inc/base_logger.hpp    
    inc/console_logger.hpp    
    inc/file_logger.hpp    
) 

set(SOURCES
    src/analyzer.cpp    
    src/async_interface.cpp    
    src/async.cpp
    src/console_logger.cpp    
    src/file_logger.cpp    
) 

add_definitions(-DASYNC_EXPORT)

add_library(${LIB_NAME} SHARED ${HEADERS} ${SOURCES})

set_target_properties(${LIB_NAME} 
    PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    PUBLIC_HEADER
        lib/inc/async/async.h
)

target_include_directories(${LIB_NAME}
    PUBLIC
        inc/async
    PRIVATE
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

# install
