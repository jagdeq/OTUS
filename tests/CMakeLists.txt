if(WITH_TESTS)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_executable(${TEST_NAME} tests.cpp)

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

    if (MSVC)
        target_compile_options(${TEST_NAME} PRIVATE
            /W4
        )
    else()
        target_compile_options(${TEST_NAME} PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()
