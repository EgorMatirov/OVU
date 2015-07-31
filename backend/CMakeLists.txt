add_subdirectory(tests/unit/c++)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
    OVUbackend_SRCS
    modules/OVU/backend.cpp
    modules/OVU/mytype.cpp
)

add_library(OVUbackend MODULE
    ${OVUbackend_SRCS}
)

add_library(OVUbackend-static STATIC
    ${OVUbackend_SRCS}
)

set_target_properties(OVUbackend PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY OVU)

set_target_properties(OVUbackend-static PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY OVU)

qt5_use_modules(OVUbackend Gui Qml Quick)
qt5_use_modules(OVUbackend-static Gui Qml Quick)

# Copy qmldir file to build dir for running in QtCreator
add_custom_target(OVUbackend-qmldir ALL
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/modules/OVU/qmldir ${CMAKE_CURRENT_BINARY_DIR}/OVU
    DEPENDS ${QMLFILES}
)

# Install plugin file
install(TARGETS OVUbackend DESTINATION ${QT_IMPORTS_DIR}/OVU/)
install(FILES   modules/OVU/qmldir DESTINATION ${QT_IMPORTS_DIR}/OVU/)

