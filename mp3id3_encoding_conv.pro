QT = core gui
TARGET = mp3id3_encoding_conv
TEMPLATE = app

HEADERS += \
    src/iconv/iconv.h \
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

LIBS += -Llib -ltag -liconv-2 -luchardet -lopencc
