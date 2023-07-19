cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION ${PATCH_VERSION})

set( PROJECT_NAME ip_filter)

project( ${PROJECT_NAME} VERSION ${PROJECT_VERSION})

set( SOURCES
  src/ip_filter.cpp
)

set( HEADERS
  include/ip_filter.h
)

add_executable( ip_filter_cli src/main.cpp )
add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(ip_filter PRIVATE include)

target_link_libraries(ip_filter_cli PRIVATE
    ip_filter
)
set_target_properties(ip_filter_cli ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

if (MSVC)
    target_compile_options(ip_filter_cli PRIVATE
        /W4
    )

else ()
    target_compile_options(ip_filter_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )


endif()

install(TARGETS ip_filter_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
include(CPack)
