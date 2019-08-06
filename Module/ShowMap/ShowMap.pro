#-------------------------------------------------
#
# Project created by QtCreator 2019-07-19T12:48:58
#
#-------------------------------------------------
QT += xml
TARGET = ShowMap
TEMPLATE = lib

DEFINES += SHOWMAP_LIBRARY
DEFINES += CORE_EXPORT=Q_DECL_IMPORT
DEFINES += GUI_EXPORT=Q_DECL_IMPORT
DEFINES += noexcept=
DEFINES += override=
DEFINES += nullptr=0
DEFINES += _USE_MATH_DEFINES
#DEFINES += NOMINMAX

#DEFINES += QT_NO_CAST_TO_ASCII

#三方库
INCLUDEPATH += E:\VBF_GlobalGIS\3rdParty\3rdParty_vs2010_x64\include

#QGIS三方库
INCLUDEPATH += ../../3rdParty/include\
               ../../3rdParty/include/core \
               ../../3rdParty/include/core/geometry \
               ../../3rdParty/include/core/layertree \
               ../../3rdParty/include/core/raster \
               ../../3rdParty/include/gui \
               ../


CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../../build/bin/Debug
    TARGET = SM_ShowMapd
    LIBS += -L../../3rdParty/lib -lqgis_cored -lqgis_guid

}else{
    DESTDIR = $$PWD/../../build/bin/Release
    TARGET = SM_ShowMap
    LIBS += -L../../3rdParty/lib -lqgis_core -lqgis_gui
}


SOURCES += SM_ShowMap.cpp

HEADERS += SM_ShowMap.h\
        showmap_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
