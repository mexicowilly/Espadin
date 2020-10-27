CMAKE_MINIMUM_REQUIRED(VERSION 3.13.4)

PROJECT(espadin CXX)

SET(ESPADIN_MAJOR_VERSION 1)
SET(ESPADIN_MINOR_VERSION 0)
SET(ESPADIN_VERSION ${ESPADIN_MAJOR_VERSION}.${ESPADIN_MINOR_VERSION})

INCLUDE(Configure.cmake)

INCLUDE_DIRECTORIES(include
                    "${CMAKE_BINARY_DIR}"
                    "${ESPADIN_CHUCHO_INCLUDE_DIR}")

LIST(APPEND ESPADIN_PUBLIC_HEADERS
     include/espadin/capabilities.hpp
     "${CMAKE_BINARY_DIR}/espadin/export.hpp"
     include/espadin/finalize.hpp
     include/espadin/user.hpp)

LIST(APPEND ESPADIN_SOURCES
     capabilities.cpp
     cJSON.c
     cJSON.h
     cjson_doc.cpp
     cjson_doc.hpp
     cjson_util.cpp
     cjson_util.hpp
     curl.cpp
     curl.hpp
     finalize.cpp
     garbage_cleaner.cpp
     garbage_cleaner.hpp
     user.cpp
     ${ESPADIN_PUBLIC_HEADERS})

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
                      "${ESPADIN_CHUCHO_LIB}")