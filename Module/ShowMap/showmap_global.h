﻿#ifndef SHOWMAP_GLOBAL_H
#define SHOWMAP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SHOWMAP_LIBRARY)
#  define SHOWMAPSHARED_EXPORT Q_DECL_EXPORT
//#define CORE_EXPORT Q_DECL_IMPORT
//#define GUI_EXPORT Q_DECL_IMPORT
#else
#  define SHOWMAPSHARED_EXPORT Q_DECL_IMPORT
#endif



#endif // SHOWMAP_GLOBAL_H
