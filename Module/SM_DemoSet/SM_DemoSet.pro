#-------------------------------------------------
#
# Project created by QtCreator 2019-07-22T16:46:15
#
#-------------------------------------------------

QT       += gui xml opengl
QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

TARGET = SM_DemoSet
TEMPLATE = lib

DEFINES += SM_DEMOSET_LIBRARY
DEFINES += CORE_EXPORT=Q_DECL_IMPORT
DEFINES += GUI_EXPORT=Q_DECL_IMPORT
DEFINES += noexcept=
DEFINES += override=
DEFINES += nullptr=0
DEFINES += _USE_MATH_DEFINES
DEFINES += VBF_TOOLSSHARED_EXPORT=Q_DECL_IMPORT
DEFINES += VBF_SLICEBYPROSHARED_EXPORT=Q_DECL_IMPORT

#3rdparty
INCLUDEPATH += E:\VBF_GlobalGIS\3rdParty\3rdParty_vs2010_x64\include

#QGIS
INCLUDEPATH += ../../../3rdParty/include\
               ../../../3rdParty/include/core \
               ../../../3rdParty/include/core/geometry \
               ../../../3rdParty/include/core/layertree \
               ../../../3rdParty/include/core/raster \
               ../../../3rdParty/include/core/layertree \
               ../../../3rdParty/include/gui \
               ../../../3rdParty/include/SliceMapTool \
               ../../../Public/Math \
               ../../


CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../../../build/bin/Debug
    TARGET = SM_DemoSetd
    LIBS += -L$$PWD/../../../3rdParty/lib -lqgis_cored -lqgis_guid -lVBF_SliceByProd

}else{
    DESTDIR = $$PWD/../../../build/bin/Release
    TARGET = SM_DemoSet
    LIBS += -L$$PWD/../../../3rdParty/lib -lqgis_core -lqgis_gui -lVBF_SliceByPro
}


SOURCES += \
    SM_DemoBase.cpp \
    SM_ShowMap.cpp \
    SM_LoaderTile.cpp \
    SM_Thread.cpp \
    SM_BarTool.cpp \
    SM_ToolPlot.cpp

HEADERS +=\
        sm_demoset_global.h \
    SM_DemoBase.h \
    SM_ShowMap.h \
    SM_LoaderTile.h \
    SM_Thread.h \
    SM_BarTool.h \
    SM_ToolPlot.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
