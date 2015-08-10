set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Test REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/backend/modules/OVU/
)

add_test_OVU(TitleHandler_test)
add_test_OVU(EntryHandler_test)
add_test_OVU(ContentHandler_test)
add_test_OVU(LinkHandler_test)
add_test_OVU(NameHandler_test)
add_test_OVU(AuthorHandler_test)

add_test_OVU(LinkElement_test)
