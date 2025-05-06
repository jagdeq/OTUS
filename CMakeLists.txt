cmake_minimum_required(VERSION 3.28.1)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(async VERSION ${PROJECT_VESRION} )

set(EXEC_NAME ${PROJECT_NAME}_cli)
set(LIB_NAME ${PROJECT_NAME})
set(TEST_NAME ${PROJECT_NAME}_test)

option(WITH_GTESTS "Whether to build tests" ON)

configure_file(version.h.in version.h)

add_executable(${EXEC_NAME} main.cpp)

set_target_properties(${EXEC_NAME} 
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

target_link_libraries(${EXEC_NAME} 
    PRIVATE
        async
)   

add_subdirectory(lib)

if(MSVC)
    target_compile_options(${EXEC_NAME} PRIVATE
        /W4
    )
else()
    target_compile_options(${EXEC_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ${EXEC_NAME} RUNTIME DESTINATION bin)
    
install(TARGETS ${LIB_NAME}
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_GTESTS)
    add_subdirectory(gtests)
    add_subdirectory(tests)
    enable_testing()
    add_test(${TEST_NAME} tests/${TEST_NAME})
endif()
