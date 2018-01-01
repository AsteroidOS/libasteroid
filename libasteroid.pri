QT += bluetooth

SOURCES += \
    $$PWD/watch.cpp \
    $$PWD/watchconnection.cpp \
    $$PWD/scanner.cpp \
    $$PWD/services/batteryservice.cpp \
    $$PWD/services/service.cpp \
    $$PWD/services/mediaservice.cpp \
    $$PWD/services/notificationservice.cpp \
    $$PWD/services/screenshotservice.cpp \
    $$PWD/services/timeservice.cpp \
    $$PWD/services/weatherservice.cpp

HEADERS += \
    $$PWD/watch.h \
    $$PWD/watchconnection.h \
    $$PWD/scanner.h \
    $$PWD/services/batteryservice.h \
    $$PWD/services/service.h \
    $$PWD/services/common.h \
    $$PWD/services/mediaservice.h \
    $$PWD/services/notificationservice.h \
    $$PWD/services/screenshotservice.h \
    $$PWD/services/timeservice.h \
    $$PWD/services/weatherservice.h
