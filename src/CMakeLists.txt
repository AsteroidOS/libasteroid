cmake_minimum_required(VERSION 3.15)
find_package(Qt5 COMPONENTS Bluetooth REQUIRED)
set(CMAKE_AUTOMOC ON)
add_library(libasteroid SHARED
    watch.cpp 
    watchconnection.cpp 
    scanner.cpp
    services/batteryservice.cpp 
    services/mediaservice.cpp
    services/notificationservice.cpp
    services/timeservice.cpp
    services/screenshotservice.cpp
    services/weatherservice.cpp 
    services/service.cpp
)
target_compile_features(libasteroid PUBLIC cxx_std_17)
target_compile_options(libasteroid PRIVATE -Wall -Wextra -pedantic -Werror)
target_link_libraries(libasteroid PRIVATE Qt5::Bluetooth)
target_include_directories(libasteroid 
    PUBLIC
        $<INSTALL_INTERFACE:.>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/services
)
install(TARGETS libasteroid)
