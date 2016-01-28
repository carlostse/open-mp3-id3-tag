#-------------------------------------------------
#
# Open MP3 ID3 Tag
#
# Author: Carlos Tse
# Email: copperoxide@gmail.com
# Date: 28 JAN 2016
#-------------------------------------------------

QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = open_mp3_id3_tag
TEMPLATE = app

CONFIG(debug, debug|release) {
    message(Debug build)
    DESTDIR = debug
} else {
    message(Release build)
    DESTDIR = release
}
OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

QMAKE_CXXFLAGS += -std=gnu++11 -Wno-unknown-pragmas -Wno-switch -Wno-unused-result
QMAKE_CXXFLAGS_DEBUG += -O0 -Wall -g
QMAKE_CXXFLAGS_RELEASE += -O2

HEADERS += \
    src/opencc/opencc.h \
    src/opencc/opencc_types.h \
    src/opencc/dictionary/text.h \
    src/opencc/dictionary/datrie.h \
    src/opencc/dictionary/abstract.h \
    src/opencc/utils.h \
    src/opencc/encoding.h \
    src/opencc/dictionary_set.h \
    src/opencc/converter.h \
    src/opencc/config_reader.h \
    src/opencc/dictionary_group.h \
    src/drop_area.h \
    src/encoding_convertor.h \
    src/common.h \
    src/tag_convertor.h \
    src/main_window.h \
    src/chinese_convertor.h

SOURCES += \
    src/opencc/opencc.c \
    src/opencc/dictionary/text.c \
    src/opencc/dictionary/datrie.c \
    src/opencc/dictionary/abstract.c \
    src/opencc/utils.c \
    src/opencc/encoding.c \
    src/opencc/dictionary_set.c \
    src/opencc/converter.c \
    src/opencc/config_reader.c \
    src/opencc/dictionary_group.c \
    src/main.cpp \
    src/drop_area.cpp \
    src/encoding_convertor.cpp \
    src/tag_convertor.cpp \
    src/main_window.cpp \
    src/chinese_convertor.cpp \
    src/common.c

FORMS +=

INCLUDEPATH += ../uchardet/src \
    ../taglib-1.9.1/ \
    ../taglib-1.9.1/taglib \
    ../taglib-1.9.1/taglib/toolkit

LIBS += -L../taglib-1.9.1/taglib -ltag \
    -L../uchardet/src -luchardet

RESOURCES = mp3id3_encoding_conv.qrc

TRANSLATIONS = ts/zhs.ts ts/zht.ts

win32 {
    RC_FILE = mp3id3_encoding_conv.rc
}

macx {
    QMAKE_CXXFLAGS += -Winconsistent-missing-override
    ICON = icon.icns
    QTPLUGIN += qtwcodecs qcncodecs
}

linux-g++ {
    LIBS += -L/lib64 -lz
    QTPLUGIN += qtwcodecs qcncodecs
}
