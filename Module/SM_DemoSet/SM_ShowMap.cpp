#include <QDebug>

#include <qgsrasterlayer.h>
#include <qgsmaplayerregistry.h>
#include <qgsproject.h>
#include <qgslayertreelayer.h>
#include <qgslayertreegroup.h>
#include <qgsvectorlayer.h>
#include <qgsmapcanvas.h>
#include <qgsmaptoolpan.h>
#include <qgscoordinateutils.h>

#include "sm_demoset_global.h"
#include "SM_ShowMap.h"
#include "SM_DemoBase.h"
#include "SM_LoaderTile.h"

SM_ShowMap::SM_ShowMap(const QString &qstrFilePath, bool bRender, QWidget* parent)
    :m_qstrFilePath(qstrFilePath),
     m_pCanvas(NULL),
     m_bLoadTiles(bRender),
     m_pLoader(NULL)
{
    Init(parent);
}

SM_ShowMap::~SM_ShowMap()
{

}

void SM_ShowMap::EnableTilesLoader(bool bTileRender)
{
    m_bLoadTiles = bTileRender;
}

void SM_ShowMap::SetTileSize(int nSize)
{
    if (!m_bLoadTiles) return;
    if(!m_pLoader)
        m_pLoader = new SM_LoaderTile(m_pCanvas,m_qstrFilePath);
    if (!m_pLoader) return;
    m_pLoader->SetTileSize(nSize);
}

void SM_ShowMap::SetSearchPath(const QString &qstrPath)
{
    if (!m_bLoadTiles) return;
    if(!m_pLoader)
        m_pLoader = new SM_LoaderTile(m_pCanvas,m_qstrFilePath);
    if (!m_pLoader) return;
    m_pLoader->SetSearchPath(qstrPath);

}

void SM_ShowMap::slotShowXY(const QgsPoint &p)
{
    //依据精度计算坐标,并得到坐标
    QStringList liststr(QgsCoordinateUtils::formatCoordinateForProject(p,m_pCanvas->mapSettings().destinationCrs(),m_unPrecision)
                        .split(","));
    m_pt.m_dx = liststr.at(0).toDouble();m_pt.m_dy = liststr.at(1).toDouble();
    emit sigXY(m_pt);
}

void SM_ShowMap::slotUpdatePrecision()
{
    m_unPrecision = QgsCoordinateUtils::calculateCoordinatePrecision(m_pCanvas->mapUnitsPerPixel(),
                                        m_pCanvas->mapSettings().destinationCrs());
}

void SM_ShowMap::ShowMap()
{
    if(!m_pCanvas) return;
    LoadMap();
    m_pCanvas->freeze(false);
    m_pCanvas->refresh();
}

void SM_ShowMap::Init(QWidget* parent)
{
    if (!m_bLoadTiles)
    {
        SM_DemoBase::Instance();
    }

    //画布
    m_pCanvas = new QgsMapCanvas(parent);
    if (!m_pCanvas) return;
    connect(m_pCanvas,SIGNAL(xyCoordinates( const QgsPoint &)),this,SLOT(slotShowXY(const QgsPoint&)));
    connect(m_pCanvas,SIGNAL(scaleChanged(double)),this,SLOT(slotUpdatePrecision()));
    //地图工具
    QgsMapToolPan* pTool= new QgsMapToolPan(m_pCanvas);
    m_pCanvas->setMapTool(pTool);

    //坐标
    m_pt.m_dx = 0; m_pt.m_dy = 0;
}

void SM_ShowMap::LoadMap()
{
    if (m_qstrFilePath.contains(".qgs") && !m_bLoadTiles)//加载工程
    {
        LoadPro();
    }
    else if(m_bLoadTiles)//加载瓦片
    {
        LoadTile();
    }
    else
    {
        LoadDataFile();//加载数据文件
    }
}


void SM_ShowMap::LoadDataFile()
{
    QgsMapLayer* pLayer = NULL;
    if(m_enumType == VECTOR)
    {
        pLayer = new QgsVectorLayer(m_qstrFilePath,"","ogr");
    }
    if(m_enumType == RASTER)
    {
        pLayer = new QgsRasterLayer(m_qstrFilePath,"","gdal");
    }

    if (!pLayer) return;

    if (!pLayer->isValid())
    {
        qDebug() << "图层创建失败,错误请见" << pLayer->error().message();
        return;
    }

    if(!pLayer->isValid()) return;

    QgsMapLayerRegistry::instance()->addMapLayer(pLayer);

    QgsMapCanvasLayer CanvasLayer(pLayer);
    QList <QgsMapCanvasLayer> listLayer;
    listLayer.append(CanvasLayer);

    if (m_pCanvas)
    m_pCanvas->setLayerSet(listLayer);
    m_pCanvas->freeze(true);
    m_pCanvas->setExtent(pLayer->extent());
}

void SM_ShowMap::LoadPro()
{
    //读取工程文件
    QFileInfo pro(m_qstrFilePath);

    QgsProject* pPro = QgsProject::instance();
    if((!pPro) || (!pPro->read(pro)))//读取工程失败
    {
        std::cout << "读取工程失败" << std::endl;
        return ;
    }

    //绑定信号槽
    //QObject::connect(pPro,SIGNAL(readProject(const QDomDocument &)),m_pCanvas,SLOT(readProject(const QDomDocument &)));

    m_pCanvas->setParallelRenderingEnabled(true);

    //设置图层
    QList <QgsMapCanvasLayer> listCanvasLayer;
    QList<QgsLayerTreeLayer*> listLayer = QgsProject::instance()->layerTreeRoot()->findLayers();
    foreach (QgsLayerTreeLayer* pLayer, listLayer)
    {
        QgsMapCanvasLayer CanvasLayer(pLayer->layer());
        listCanvasLayer.append(CanvasLayer);
    }

    m_pCanvas->setLayerSet(listCanvasLayer);
    m_pCanvas->freeze(true);
    m_pCanvas->zoomToFullExtent();
}

void SM_ShowMap::LoadTile()
{
    if(!m_pLoader)
        m_pLoader = new SM_LoaderTile(m_pCanvas,m_qstrFilePath);
    if (!m_pLoader) return;
    m_pLoader->Init();

}
