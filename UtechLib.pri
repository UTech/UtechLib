!contains(UTECHLIB,defined){
	QT +=  sql
	
	win32{
	  CONFIG(debug, debug|release) {
		  LIBS += $$PWD/lib/win/libUtechQtExtd.a
	  }
	  else {
		  LIBS += $$PWD/lib/win/libUtechQtExt.a
	  }
	}
	
	unix{
	  CONFIG(debug, debug|release) {
		  LIBS += $$PWD/lib/unix/libUtechQtExtd.a
	  }
	  else {
		  LIBS += $$PWD/lib/unix/libUtechQtExt.a
	  }
	}
	
	INCLUDEPATH += $$PWD/include $$PWD/src/3rdparty/UXBase64/xbase64
	RESOURCES += $$PWD/src/images/UImgLib.qrc
	UTECHLIB += defined
	message("UtechLib configured OK.")
}
