if (WITH_GTESTS)
    add_executable(${TEST_NAME} tests.cpp)

    set_target_properties(${TEST_NAME}
        PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(${TEST_NAME}
        ${LIB_NAME}
        gtest_main
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
endif()
