cmake_minimum_required(VERSION 3.16)
project(nuixt VERSION 1.0.0 LANGUAGES CXX OBJCXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_OBJCXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(NUIXT_BUILD_EXAMPLES "Build example applications" ON)

# Core sources
set(NUIXT_SOURCES src/nuixt/Window.cpp)

# Platform-specific sources
if(WIN32)
    list(APPEND NUIXT_SOURCES src/win32/Win32Window.cpp)
elseif(APPLE)
    list(APPEND NUIXT_SOURCES
        src/apple/AppKitWindow.mm
        src/apple/AppDelegate.mm
    )
elseif(UNIX AND NOT APPLE)
    list(APPEND NUIXT_SOURCES src/gtk/GTKWindow.cpp)
endif()

# Main library target
add_library(nuixt STATIC ${NUIXT_SOURCES})
target_include_directories(nuixt PUBLIC include)

# Platform-specific linking
if(WIN32)
    target_link_libraries(nuixt PRIVATE user32 gdi32)
elseif(APPLE)
    find_library(COCOA_FRAMEWORK Cocoa REQUIRED)
    target_link_libraries(nuixt PRIVATE ${COCOA_FRAMEWORK})
elseif(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK REQUIRED gtk+-3.0)
    target_include_directories(nuixt PRIVATE ${GTK_INCLUDE_DIRS})
    target_link_libraries(nuixt PRIVATE ${GTK_LIBRARIES})
endif()

# Examples
if(NUIXT_BUILD_EXAMPLES)
    if(APPLE)
        add_executable(hello_window MACOSX_BUNDLE examples/hello_window/main.cpp)

        set_target_properties(hello_window PROPERTIES
            OUTPUT_NAME "Hello Window"
            MACOSX_BUNDLE_BUNDLE_NAME "Hello Window"
            MACOSX_BUNDLE_GUI_IDENTIFIER "com.nuixt.hello-window"
            MACOSX_BUNDLE_BUNDLE_VERSION "1.0.0"
            MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
        )

        add_executable(hello_menu_bar MACOSX_BUNDLE examples/hello_menu_bar/main.cpp)

        set_target_properties(hello_menu_bar PROPERTIES
            OUTPUT_NAME "Hello Menu Bar"
            MACOSX_BUNDLE_BUNDLE_NAME "Hello Menu Bar"
            MACOSX_BUNDLE_GUI_IDENTIFIER "com.nuixt.hello-menu-bar"
            MACOSX_BUNDLE_BUNDLE_VERSION "1.0.0"
            MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
        )
    else()
        add_executable(hello_window examples/hello_window/main.cpp)
    endif()
    target_link_libraries(hello_window PRIVATE nuixt)
    target_link_libraries(hello_menu_bar PRIVATE nuixt)
endif()
