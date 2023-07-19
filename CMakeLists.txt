cmake_minimum_required(VERSION 3.12)

set( PROJECT_NAME ip_filter)

project( ${PROJECT_NAME} )

set( SOURCES
  src/ip_filter.cpp
  src/main.cpp
)

set(HEADERS
include/ip_filter.h
)

add_executable( ${PROJECT_NAME} ${SOURCES} ${HEADERS} )

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )

endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
include(CPack)
