macro (add_test_OVU name)
    add_executable(${name} ${name}.cpp)
    add_test(${name} ${name})

    set_property(TEST ${name} PROPERTY
        ENVIRONMENT "LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/backend/OVU"
    )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors -pedantic-errors -Werror -Wextra -Wall -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Wmissing-declarations -std=c++11")

    target_link_libraries(${name} Qt5::Test OVUbackend)
endmacro (add_test_OVU)
