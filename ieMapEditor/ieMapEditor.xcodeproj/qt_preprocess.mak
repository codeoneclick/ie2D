#############################################################################
# Makefile for building: ieMapEditor.app/Contents/MacOS/ieMapEditor
# Generated by qmake (3.0) (Qt 5.2.0)
# Project:  ieMapEditor.pro
# Template: app
# Command: /Applications/Qt/5.2.0/5.2.0/clang_64/bin/qmake -spec macx-xcode -o ieMapEditor.xcodeproj/project.pbxproj ieMapEditor.pro
#############################################################################

MAKEFILE      = project.pbxproj

MOC       = /Applications/Qt/5.2.0/5.2.0/clang_64/bin/moc
UIC       = /Applications/Qt/5.2.0/5.2.0/clang_64/bin/uic
LEX       = flex
LEXFLAGS  = 
YACC      = yacc
YACCFLAGS = -d
DEFINES       = -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB
INCPATH       = -I/Applications/Qt/5.2.0/5.2.0/clang_64/mkspecs/macx-clang -I. -I/Applications/Qt/5.2.0/5.2.0/clang_64/lib/QtWidgets.framework/Versions/5/Headers -I/Applications/Qt/5.2.0/5.2.0/clang_64/lib/QtGui.framework/Versions/5/Headers -I/Applications/Qt/5.2.0/5.2.0/clang_64/lib/QtCore.framework/Versions/5/Headers -I. -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/System/Library/Frameworks/AGL.framework/Headers -I. -F/Applications/Qt/5.2.0/5.2.0/clang_64/lib
DEL_FILE  = rm -f
MOVE      = mv -f

IMAGES = 
PARSERS =
preprocess: $(PARSERS) compilers
clean preprocess_clean: parser_clean compiler_clean

parser_clean:
mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

check: first

compilers: ./moc_ieMapEditor.cpp ./ui_ieMapEditor.h
compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_rcc_make_all:
compiler_rcc_clean:
compiler_moc_header_make_all: moc_ieMapEditor.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_ieMapEditor.cpp
moc_ieMapEditor.cpp: /Applications/Qt/5.2.0/5.2.0/clang_64/lib/QtWidgets.framework/Versions/5/Headers/QMainWindow \
		Sources/ieMapEditor.h
	/Applications/Qt/5.2.0/5.2.0/clang_64/bin/moc $(DEFINES) -D__APPLE__ -D__GNUC__=4 $(INCPATH) Sources/ieMapEditor.h -o moc_ieMapEditor.cpp

compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_ieMapEditor.h
compiler_uic_clean:
	-$(DEL_FILE) ui_ieMapEditor.h
ui_ieMapEditor.h: UI/ieMapEditor.ui
	/Applications/Qt/5.2.0/5.2.0/clang_64/bin/uic UI/ieMapEditor.ui -o ui_ieMapEditor.h

compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 
