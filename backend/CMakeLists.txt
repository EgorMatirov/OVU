add_subdirectory(tests/unit/c++)

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

add_custom_backend_module("OVU" "${OVUbackend_SRCS}")
