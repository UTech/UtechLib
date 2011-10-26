message("Loaded UXBase64.pro Project")

INCLUDEPATH += $$PWD/xbase64
DEPENDPATH += $$PWD/xbase64
VPATH += $$PWD/xbase64

# Input
HEADERS += xbase64.h \
           xbcdx.h \
           xbconfig.h \
           xbdate.h \
           xbdbf.h \
           xbexp.h \
           xbfile.h \
           xbfilter.h \
           xbindex.h \
           xblock.h \
           xbndx.h \
           xbntx.h \
           xbretcod.h \
           xbstring.h \
           xbtypes.h \
           xbwincfg.h
SOURCES += xbase64.cpp \
           xbcdx.cpp \
           xbdate.cpp \
           xbdbf.cpp \
           xbexp.cpp \
           xbexpfnc.cpp \
           xbexpprc.cpp \
           xbfields.cpp \
           xbfile.cpp \
           xbfilter.cpp \
           xbindex.cpp \
           xblock.cpp \
           xbmemo.cpp \
           xbndx.cpp \
           xbntx.cpp \
           xbstring.cpp
