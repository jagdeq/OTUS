cmake_minimum_required(VERSION 3.28.1)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VESRION})

set(LIB_NAME helloworld)
set(EXEC_NAME helloworld_cli)
set(TEST_NAME test_version)

# Из-за выбора через консоль убрал значение по умолчанию
# option(WITH_BOOST_TEST "Whether to build Boost test" OFF)
# option(WITH_GOOGLE_TEST "Whether to build Google test" ON)

configure_file(version.h.in version.h)

add_executable(${EXEC_NAME} src/main.cpp)
add_library(${LIB_NAME} src/lib.cpp)

set_target_properties(${EXEC_NAME} ${LIB_NAME} 
    PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(${LIB_NAME}
    PRIVATE
        "${CMAKE_BINARY_DIR}"
    PUBLIC 
        inc
)

target_link_libraries(${EXEC_NAME} 
    PRIVATE
        ${LIB_NAME}
)   

if(WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_executable(${TEST_NAME} tests/test_version.cpp)

    set_target_properties(${TEST_NAME} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(${TEST_NAME} PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )

    target_link_libraries(${TEST_NAME}
        ${Boost_LIBRARIES}
        ${LIB_NAME}
    )
elseif(WITH_GOOGLE_TEST)
    find_package(GTest REQUIRED)
    add_executable(${TEST_NAME} tests/test_version_gtest.cpp)

    set_target_properties(${TEST_NAME} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(${TEST_NAME}
        ${GTEST_LIBRARIES}
        ${LIB_NAME}
    )
endif()

if (MSVC)
    target_compile_options(${EXEC_NAME} PRIVATE
        /W4
    )

    target_compile_options(${LIB_NAME} PRIVATE
        /W4
    )

    if(WITH_BOOST_TEST OR WITH_GOOGLE_TEST)
        target_compile_options(${TEST_NAME} PRIVATE
            /W4
        )
    endif()
else()
    target_compile_options(${EXEC_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )

    target_compile_options(${LIB_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )

    if(WITH_BOOST_TEST OR WITH_GOOGLE_TEST)
        target_compile_options(${TEST_NAME} PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS ${EXEC_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_BOOST_TEST OR WITH_GOOGLE_TEST)
    enable_testing()
    add_test(test_version ${TEST_NAME})
endif()
