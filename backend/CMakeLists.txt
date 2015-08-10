add_subdirectory(tests/unit/c++)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/OVU
)

set(
    OVUbackend_SRCS
    modules/OVU/backend.cpp
    modules/OVU/Feed.cpp
    modules/OVU/FeedModel.cpp
    modules/OVU/Elements/Element.cpp
    modules/OVU/Elements/EntryElement.cpp
    modules/OVU/Elements/TitleElement.cpp
    modules/OVU/Elements/ContentElement.cpp
    modules/OVU/Elements/LinkElement.cpp
    modules/OVU/Elements/ThumbnailElement.cpp
    modules/OVU/Elements/AcquisitionElement.cpp
    modules/OVU/Elements/NavigationFeedElement.cpp
    modules/OVU/Elements/AuthorElement.cpp
    modules/OVU/Elements/NameElement.cpp
    modules/OVU/Elements/NextLinkElement.cpp
    modules/OVU/Handlers/Handler.cpp
    modules/OVU/Handlers/HandlersMap.cpp
    modules/OVU/Handlers/EntryHandler.cpp
    modules/OVU/Handlers/TitleHandler.cpp
    modules/OVU/Handlers/ContentHandler.cpp
    modules/OVU/Handlers/LinkHandler.cpp
    modules/OVU/Handlers/AuthorHandler.cpp
    modules/OVU/Handlers/NameHandler.cpp
)

add_library(OVUbackend MODULE
    ${OVUbackend_SRCS}
)

set_target_properties(OVUbackend PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY OVU)

qt5_use_modules(OVUbackend Gui Qml Quick)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors -pedantic-errors -Werror -Wextra -Wall -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Wmissing-declarations -std=c++11")

# Copy qmldir file to build dir for running in QtCreator
add_custom_target(OVUbackend-qmldir ALL
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/modules/OVU/qmldir ${CMAKE_CURRENT_BINARY_DIR}/OVU
    DEPENDS ${QMLFILES}
)

# Install plugin file
install(TARGETS OVUbackend DESTINATION ${QT_IMPORTS_DIR}/OVU/)
install(FILES   modules/OVU/qmldir DESTINATION ${QT_IMPORTS_DIR}/OVU/)
