cmake_minimum_required(VERSION 3.28.1)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VESRION})

set(LIB_NAME ip_filter_lib)
set(EXEC_NAME ip_filter)
set(TEST_NAME test_filter)

option(WITH_TESTS "Whether to build tests" ON)

configure_file(version.h.in version.h)

add_executable(${EXEC_NAME} main.cpp)
# add_library(${LIB_NAME} src/lib.cpp)

set_target_properties(${EXEC_NAME} 
    PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)

target_link_libraries(${EXEC_NAME} 
    PRIVATE
        ${LIB_NAME}
)   

add_subdirectory(lib)
add_subdirectory(tests)

if (MSVC)
    target_compile_options(${EXEC_NAME} PRIVATE
        /W4
    )
else()
    target_compile_options(${EXEC_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ${EXEC_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_TESTS)
    enable_testing()
    add_test(test_filter tests/${TEST_NAME})
endif()
