QT       += core gui
QT       += opengl
QT       += openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 c11

TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../c-part/backend.c \
    ../c-part/memory_work.c \
    ../c-part/parce_f.c \
    ../c-part/parce_v.c \
    ../c-part/rotation.c \
    gifimage/dgif_lib.c \
    gifimage/egif_lib.c \
    gifimage/gif_err.c \
    gifimage/gif_font.c \
    gifimage/gif_hash.c \
    gifimage/gifalloc.c \
    gifimage/qgifimage.cpp \
    gifimage/quantize.c \
    graphicwindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../c-part/backend.h \
    gifimage/gif_hash.h \
    gifimage/gif_lib.h \
    gifimage/gif_lib_private.h \
    gifimage/qgifglobal.h \
    gifimage/qgifimage.h \
    gifimage/qgifimage_p.h \
    graphicwindow.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    mainwindow.ui

RESOURCES += \
#    ../../misc/images/resourses.qrc

macx:ICON = img/icon.icns

SUBDIRS += \
    gifimage/doc/snippets/doc_src_qtgifimage.pro \
    gifimage/doc/snippets/doc_src_qtgifimage.pro \
    gifimage/gifimage.pro \
    gifimage/gifimage.pro

DISTFILES += \
    gifimage/doc/qtgifimage.qdocconf \
    gifimage/doc/src/examples.qdoc \
    gifimage/doc/src/index.qdoc \
    gifimage/doc/src/qtgifimage.qdoc \
    gifimage/doc/src/usage.qdoc \
    gifimage/giflib/AUTHORS \
    gifimage/giflib/COPYING \
    gifimage/giflib/README \
    gifimage/qtgifimage.pri
