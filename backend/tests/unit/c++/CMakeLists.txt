set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Test REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/backend/modules/OVU/
)

add_test_OVU(simple)
