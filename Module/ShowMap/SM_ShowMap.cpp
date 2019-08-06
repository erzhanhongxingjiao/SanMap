#include <QDebug>

#include <qgsrasterlayer.h>
#include <qgsmaplayerregistry.h>
#include <qgsproviderregistry.h>
#include <qgsvectorlayer.h>
#include <qgsmapcanvas.h>
#include "showmap_global.h"
#include "SM_ShowMap.h"


SM_ShowMap::SM_ShowMap(const QString &qstrFilePath, Datatype Type, QWidget* parent)
    :m_qstrFilePath(qstrFilePath),
     m_enumType(Type),
     m_pCanvas(new QgsMapCanvas(parent))
{
    Init();
}

SM_ShowMap::~SM_ShowMap()
{

}

void SM_ShowMap::ShowMap()
{
    m_pCanvas->refresh();
}

void SM_ShowMap::Init()
{
    //设置插件及资源目录前缀
    QDir dir(qApp->applicationDirPath());//获取应用程序所在路径

    QString strAppPath(dir.absolutePath());
    //QString strPrifixPath  = strAppPath + "/QGIS_Plugins";
    //QString strResPrefixPath = QString::fromStdString(VBF_GetSystem()->GetDataPath()); //获取资源路径前缀

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

    LoadData();
}

void SM_ShowMap::LoadData()
{
    QgsMapLayer* pLayer = NULL;
    if(m_enumType == VECTOR)
    {
        pLayer = new QgsVectorLayer(m_qstrFilePath,"","ogr");
    }
    if(m_enumType == RASTER)
    {
        pLayer = new QgsRasterLayer(m_qstrFilePath);
    }

    if (!pLayer->isValid())
    {
        qDebug() << "图层创建失败,错误请见" << pLayer->error().message();
        return;
    }

    QgsMapLayerRegistry::instance()->addMapLayer(pLayer);

    QgsMapCanvasLayer pCanvasLayer(pLayer);
    QList <QgsMapCanvasLayer> listLayer;
    listLayer.append(pCanvasLayer);

    if (m_pCanvas)
    m_pCanvas->setLayerSet(listLayer);
}
