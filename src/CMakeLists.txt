cmake_minimum_required(VERSION 3.15)
find_package(Qt5 COMPONENTS Bluetooth REQUIRED)
add_library(asteroid SHARED
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
target_compile_features(asteroid PUBLIC cxx_std_17)
set_target_properties(asteroid PROPERTIES AUTOMOC ON)
target_compile_options(asteroid PRIVATE -Wall -Wextra -pedantic -Werror)
target_link_libraries(asteroid PRIVATE Qt5::Bluetooth)
target_include_directories(asteroid
    PUBLIC
        $<INSTALL_INTERFACE:.>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/services
)
install(TARGETS asteroid)
