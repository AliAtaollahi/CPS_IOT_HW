cmake_minimum_required(VERSION 3.5)

project(MonitoringSystem VERSION 0.1 LANGUAGES CXX)

# Set C++ standard and other settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required Qt components, including Widgets and Network
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

# Set automatic handling of Qt resources
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Define project sources
set(PROJECT_SOURCES
    main.cpp
    cpsmainwindow.cpp
    cpsmainwindow.h
    cpssocket.cpp   # Add your socket source files here
    cpssocket.h
)

# Set icon resource for Windows
set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/Ut.ico")

# Check Qt version and configure target accordingly
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MonitoringSystem
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Ut.ico
        ${APP_ICON_RESOURCE_WINDOWS}
        cpshistorywindow.h cpshistorywindow.cpp
        cpstextfield.h cpstextfield.cpp
        cpsbutton.h cpsbutton.cpp
        cpslabel.h cpslabel.cpp
        cpswindowsapitools.h
        cpsapplication.h cpsapplication.cpp
    )
else()
    if(ANDROID)
        add_library(MonitoringSystem SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(MonitoringSystem
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Link Qt modules to the executable
target_link_libraries(MonitoringSystem PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

# Set target properties
if(WIN32)
    target_link_libraries(MonitoringSystem PRIVATE dwmapi) # Link additional Windows libraries if needed
endif()

# Configure target properties
set_target_properties(MonitoringSystem PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Install target
include(GNUInstallDirs)
install(TARGETS MonitoringSystem
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize executable target for Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MonitoringSystem)
endif()
