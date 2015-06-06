SOURCES += \
    main.cpp \
    mainwindow.cpp \
    taskselectionwindow.cpp \
    validationwindow.cpp \
    schedulingwindow.cpp \
    projectmanager.cpp \
    schedulingmanager.cpp \
    uniquetask.cpp \
    blendtask.cpp \
    task.cpp \
    project.cpp \
    scheduling.cpp \
    abstractcontainer.tpp \
    abstractbuilder.cpp \
    xmlbuilder.cpp \
    iomanager.cpp

HEADERS += \
    mainwindow.h \
    calendarexception.h \
    taskselectionwindow.h \
    validationwindow.h \
    schedulingwindow.h \
    projectmanager.h \
    schedulingmanager.h \
    uniquetask.h \
    blendtask.h \
    task.h \
    project.h \
    scheduling.h \
    abstractcontainer.h \
    abstractbuilder.h \
    xmlbuilder.h \
    iomanager.h

FORMS += \
    mainwindow.ui

QT += widgets\
        xml
