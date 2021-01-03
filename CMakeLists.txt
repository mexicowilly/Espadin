CMAKE_MINIMUM_REQUIRED(VERSION 3.13.4)

PROJECT(espadin CXX C)

SET(ESPADIN_MAJOR_VERSION 1)
SET(ESPADIN_MINOR_VERSION 0)
SET(ESPADIN_VERSION ${ESPADIN_MAJOR_VERSION}.${ESPADIN_MINOR_VERSION})

INCLUDE(Configure.cmake)

INCLUDE_DIRECTORIES(include
                    "${CMAKE_BINARY_DIR}"
                    "${ESPADIN_CHUCHO_INCLUDE_DIR}")

LIST(APPEND ESPADIN_PUBLIC_HEADERS
     include/espadin/about.hpp
     include/espadin/capabilities.hpp
     include/espadin/comment.hpp
     include/espadin/comments_group.hpp
     include/espadin/content_hints.hpp
     include/espadin/content_restrictions.hpp
     include/espadin/drive.hpp
     include/espadin/drive_theme.hpp
     include/espadin/exception.hpp
     "${CMAKE_BINARY_DIR}/espadin/export.hpp"
     include/espadin/file.hpp
     include/espadin/files_group.hpp
     include/espadin/finalize.hpp
     include/espadin/image_media_metadata.hpp
     include/espadin/permission.hpp
     include/espadin/permissions_group.hpp
     include/espadin/replies_group.hpp
     include/espadin/reply.hpp
     include/espadin/shortcut_details.hpp
     include/espadin/storage_quota.hpp
     include/espadin/user.hpp
     include/espadin/video_media_metadata.hpp)

LIST(APPEND ESPADIN_SOURCES
     about.cpp
     calendar.hpp
     capabilities.cpp
     comment.cpp
     comments_group.cpp
     content_hints.cpp
     content_restrictions.cpp
     cJSON.c
     cJSON.h
     cjson_doc.cpp
     cjson_doc.hpp
     cjson_util.cpp
     cjson_util.hpp
     curl.cpp
     curl.hpp
     drive_theme.cpp
     exception.cpp
     drive.cpp
     file.cpp
     files_group.cpp
     finalize.cpp
     garbage_cleaner.cpp
     garbage_cleaner.hpp
     image_media_metadata.cpp
     permission.cpp
     permissions_group.cpp
     replies_group.cpp
     reply.cpp
     request.cpp
     request.hpp
     resumable_file_upload.cpp
     resumable_file_upload.hpp
     shortcut_details.cpp
     storage_quota.cpp
     user.cpp
     video_media_metadata.cpp
     ${ESPADIN_PUBLIC_HEADERS})

IF(ESPADIN_POSIX)
    LIST(APPEND ESPADIN_SOURCES
         platform/posix/calendar_posix.cpp)
ENDIF()

IF(ENABLE_SHARED)
    ADD_LIBRARY(espadin SHARED ${ESPADIN_SOURCES})
    SET_TARGET_PROPERTIES(espadin PROPERTIES
                          VERSION ${ESPADIN_VERSION}
                          SOVERSION ${ESPADIN_MAJOR_VERSION}
                          PUBLIC_HEADER "${ESPADIN_PUBLIC_HEADERS}"
                          FRAMEWORK ${ENABLE_FRAMEWORK})
    IF(DEFINED ESPADIN_SO_FLAGS)
        SET_TARGET_PROPERTIES(espadin PROPERTIES
                              COMPILE_FLAGS "${ESPADIN_SO_FLAGS}")
    ENDIF()
    IF(ESPADIN_WINDOWS)
        SET(ESPADIN_RT_DEST bin)
    ELSE()
        SET(ESPADIN_RT_DEST lib)
    ENDIF()
    INSTALL(TARGETS espadin
            ARCHIVE DESTINATION lib
            LIBRARY DESTINATION lib
            RUNTIME DESTINATION ${ESPADIN_RT_DEST}
            FRAMEWORK DESTINATION /Library/Frameworks
            PUBLIC_HEADER DESTINATION include/espadin)
ELSE()
    ADD_LIBRARY(espadin STATIC ${ESPADIN_SOURCES})
    SET_TARGET_PROPERTIES(espadin PROPERTIES
                          PUBLIC_HEADER "${ESPADIN_PUBLIC_HEADERS}")
    INSTALL(TARGETS espadin
            ARCHIVE DESTINATION lib
            PUBLIC_HEADER DESTINATION include/espadin)
ENDIF()

TARGET_LINK_LIBRARIES(espadin
                      "${ESPADIN_CHUCHO_LIB}"
                      CURL::libcurl
                      ${ESPADIN_FS_LIB})

ADD_SUBDIRECTORY(test)