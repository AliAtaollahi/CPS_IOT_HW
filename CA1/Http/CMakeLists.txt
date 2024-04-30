cmake_minimum_required(VERSION 3.14)

project(Http LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS HttpServer)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)



add_executable(Http
  main.cpp
  customizedhttpserver.h customizedhttpserver.cpp
  request.h request.cpp
  response.h response.cpp
  employee.h employee.cpp
  employeesdatabase.h employeesdatabase.cpp
)

target_link_libraries(Http Qt${QT_VERSION_MAJOR}::Core Qt6::Network Qt6::HttpServer)


include(GNUInstallDirs)
install(TARGETS Http
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

