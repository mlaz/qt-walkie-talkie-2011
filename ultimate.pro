QT += multimedia \
network

OTHER_FILES += \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog

HEADERS += \
    mainwindow.h \
    snd_facility.h \
    microphone.h \
    ntw_facility.h \
    speaker.h

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    snd_facility.cpp \
    microphone.cpp \
    ntw_facility.cpp \
    speaker.cpp

FORMS += \
    mainwindow.ui

maemo5 {
    target.path = /opt/ultimate/bin
    INSTALLS += target
}

maemo5 {
    target.path = /opt/ultimate/bin
    INSTALLS += target
}

maemo5 {
    target.path = /opt/ultimate/bin
    INSTALLS += target
}
