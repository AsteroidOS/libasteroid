cmake_minimum_required(VERSION 3.15)
project(libasteroid)
find_package(Qt5 COMPONENTS Bluetooth REQUIRED)
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
add_library(libasteroid SHARED
    watch.cpp 
    watchconnection.cpp 
    scanner.cpp
    services/batteryservice.cpp 
    services/mediaservice.cpp
    services/notificationservice.cpp
    services/timeservice.cpp
    services/weatherservice.cpp 
)
target_compile_features(libasteroid PUBLIC cxx_std_17)
target_link_libraries(libasteroid PRIVATE Qt5::Bluetooth)
install(TARGETS libasteroid)
