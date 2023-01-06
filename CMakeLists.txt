cmake_minimum_required(VERSION 3.24)

project(LD52)

set(CMAKE_MODULE_PATH
    $ENV{CMAKE_MODULE_PATH}
    ${PROJECT_SOURCE_DIR}/cmake
)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo"
        CACHE STRING "Build configuration 'Release', 'Debug', or
        'RelWithDebInfo'."
        FORCE)
endif()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib)

option(USE_SYSTEM_DEPS "Use system version of dependencies" OFF)

add_subdirectory(external)
add_subdirectory(src)

if (UNIX)
    configure_file(dist/com.ldjam.ananace.LD52.desktop.in
        dist/com.ldjam.ananace.LD52.desktop)

    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/dist/com.ldjam.ananace.LD52.desktop
        DESTINATION share/applications
    )
    install(FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/dist/com.ldjam.ananace.LD52.png
        DESTINATION share/icons/hicolor/512x512/apps
    )
endif()
