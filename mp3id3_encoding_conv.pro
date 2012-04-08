QT = core gui
TARGET = open_mp3_id3_tag
TEMPLATE = app

HEADERS += \
    src/uchardet/uchardet.h \
    src/taglib/tag.h \
    src/taglib/fileref.h \
    src/encoding_convertor.h \
    src/common.h \
    src/tag_convertor.h \
    src/main_window.h \
    src/chinese_convertor.h

SOURCES += \
    src/main.cpp \
    src/encoding_convertor.cpp \
    src/tag_convertor.cpp \
    src/main_window.cpp \
    src/chinese_convertor.cpp

FORMS +=

LIBS += -Llib -ltag -luchardet -lopencc

RESOURCES = mp3id3_encoding_conv.qrc

TRANSLATIONS = ts/zhs.ts ts/zht.ts

CONFIG(debug, debug|release) {
    message(Debug build)
    DESTDIR = debug
    OBJECTS_DIR = debug/obj
} else {
    message(Release build)
    DESTDIR = release
    OBJECTS_DIR = release/obj
}

win32 {
    RC_FILE = mp3id3_encoding_conv.rc
}

macx {
    ICON = icon.icns
}
