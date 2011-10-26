CONFIG += debug_and_release debug_and_release_target build_all

DEPENDPATH += engine gui images numberToStrConverter printdocs sql
VPATH += engine gui images numberToStrConverter printdocs sql
INCLUDEPATH += engine gui images numberToStrConverter printdocs sql

QT +=  sql
TARGET = UtechQtExt
CONFIG(debug, debug|release) {
     win32: TARGET = $$join(TARGET,,,d)
	 unix: TARGET = $$join(TARGET,,,_debug)
}

DEFINES += UTECHLIB_LIBRARY
TEMPLATE = lib
CONFIG += static

#xBase64 lib integration
include("3rdparty/UXBase64/UXBase64.pro")

HEADERS += UMath.h \
			UPopulateTextTableCells.h \
			UStandardDelegate.h \
			UDebugForm.h \
			UPostupForm.h \
			UPrintForm.h \
			UNumberToStringConverter.h \
			UPrintDocsTemplates.h \
			USqlAccessible.h \
			UTableWidgetSqlExt.h \
			U2List.h
SOURCES += UMath.cpp \
			UPopulateTextTableCells.cpp \
			UStandardDelegate.cpp \
			UDebugForm.cpp \
			UPostupForm.cpp \
			UPrintForm.cpp \
			UNumberToStringConverter.cpp \
			UPrintDocsTemplates.cpp \
			USqlAccessible.cpp \
			UTableWidgetSqlExt.cpp \
			U2List.cpp
FORMS += UDebugForm.ui \
		UPostupForm.ui \
		UPrintForm.ui
			
RESOURCES += images/UImgLib.qrc

win32 : DESTDIR = ../lib/win
unix : DESTDIR = ../lib/unix

UI_HEADERS_DIR = ui_headers
win32{
  CONFIG(debug, debug|release) {
	OBJECTS_DIR = ../tmp/win/debug
	MOC_DIR = ../tmp/win/debug
	UI_SOURCES_DIR = ../tmp/win/debug
	RCC_DIR = ../tmp/win/debug
  } 
  else {
	OBJECTS_DIR = ../tmp/win/release
	MOC_DIR = ../tmp/win/release
	UI_SOURCES_DIR = ../tmp/win/release
	RCC_DIR = ../tmp/win/release
  }
}

unix{
  CONFIG(debug, debug|release) {
	OBJECTS_DIR = ../tmp/linux/debug
	MOC_DIR = ../tmp/linux/debug
	UI_SOURCES_DIR = ../tmp/linux/debug
	RCC_DIR = ../tmp/linux/debug
  } 
  else {
	OBJECTS_DIR = ../tmp/linux/release
	MOC_DIR = ../tmp/linux/release
	UI_SOURCES_DIR = ../tmp/linux/release
	RCC_DIR = ../tmp/linux/release
  }
}
