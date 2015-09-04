macro (add_custom_backend_module name sources)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/${name}
)

    add_library(${name}backend MODULE
        ${sources}
    )

    set_target_properties(${name}backend PROPERTIES
             LIBRARY_OUTPUT_DIRECTORY ${name})

    qt5_use_modules(${name}backend Gui Qml Quick)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors -pedantic-errors -Werror -Wextra -Wall -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Wmissing-declarations -std=c++11")

    # Copy qmldir file to build dir for running in QtCreator
    add_custom_target(${name}backend-qmldir ALL
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/modules/${name}/qmldir
        ${CMAKE_CURRENT_BINARY_DIR}/${name}
        DEPENDS ${QMLFILES}
    )

    # Install plugin file
    install(TARGETS ${name}backend DESTINATION ${QT_IMPORTS_DIR}/${name}/)
    install(FILES   modules/${name}/qmldir DESTINATION ${QT_IMPORTS_DIR}/${name}/)

endmacro (add_custom_backend_module)
