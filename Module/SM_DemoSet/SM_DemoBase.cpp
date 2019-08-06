#include <iostream>

#include <QApplication>
#include <QDebug>

#include <qgsproviderregistry.h>
#include <qgsapplication.h>

#include "SM_DemoBase.h"

SM_DemoBase::SM_DemoBase()
{
    Init();
}

void SM_DemoBase::Init()
{
    //设置插件及资源目录前缀
    QDir dir(qApp->applicationDirPath());//获取应用程序所在路径

    QString strAppPath(dir.absolutePath());
    QgsProviderRegistry::instance( strAppPath + "/QGIS_Plugins");//注册插件
    qDebug()<<"插件目录为" + strAppPath + "/QGIS_Plugins";

    //设置资源目录
    QgsApplication::setPkgDataPath(strAppPath);

    //设置GDAL_DATA
    QString strENVValue = strAppPath + "/resources/gdal_data";
    if (!qputenv( "GDAL_DATA",  strENVValue.toStdString().c_str() ))
    {
        std::cout << "GDAL_DATA设置失败" << std::endl;
    }
}

SM_DemoBase::~SM_DemoBase()
{

}

SM_DemoBase *SM_DemoBase::Instance()
{

     static SM_DemoBase* pIns = new SM_DemoBase();
     return pIns;
}

