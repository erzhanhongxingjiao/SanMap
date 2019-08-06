#include <QGLWidget>


#include <qgsproject.h>
#include <qgsmapcanvasmap.h>
#include <qgslayertreegroup.h>
#include <qgslayertreelayer.h>

#include "SM_Thread.h"
#include "SM_LoaderTile.h"

VBF_DEMTEXENGINECONFIGPAR  s_ConfigPar;
VBF_MERCATORPAR g_MercaPar;
SM_LoaderTile::SM_LoaderTile(QgsMapCanvas *pCanvas, QString &path, QObject *parent)
    : QObject(parent),
      m_pCanvas(pCanvas),
      m_pTool(NULL),
      m_bLoacal(false),
      m_nSzie(256),
      m_pthLoad(NULL),
      m_qstrPath(path)

{
        QSharedPointer <QgsMapCanvasMap> spMap(new QgsMapCanvasMap(pCanvas));
        m_spMap = spMap;
}

SM_LoaderTile::~SM_LoaderTile()
{
    if (m_pthLoad)
    {
        m_pthLoad->Cancel();
        m_pthLoad->quit();
        m_pthLoad->wait();
        m_pthLoad->deleteLater();
    }
}

void SM_LoaderTile::Init()
{
    if (m_qstrPath.contains(".qgs")) //切图工具只支持加载qgis工程
    {
        m_pTool = VBF_CreateToolSliceMapByPro(m_qstrPath.toStdString(),false,m_nSzie);
        m_pthLoad = new SM_Thread();
        if (!m_pthLoad || !m_pTool)
            disconnect(m_pCanvas,SIGNAL(extentsChanged()),this, SLOT(slotExtentChanged()));
        else
        {
            m_pthLoad->SetTileLoader(this);
            m_pthLoad->start();

        }

    }
    else
    {
        m_bLoacal = true;

    }

    InitCanvas();


    //当地图范围改变时触发
    connect(m_pCanvas,SIGNAL(extentsChanged()),this, SLOT(slotExtentChanged()));

    //当渲染完成时触发
    connect(this,SIGNAL(sigRenderFinish()),this,SLOT(slotRenderFinish()));
}


void SM_LoaderTile::slotExtentChanged()
{

    if (!m_pCanvas) return;

    if (m_bLoacal)
    {
        LoadLocal();

        //显示地图
        m_spMap.data()->setContent(m_Map,m_pCanvas->extent());
        return;
    }
    m_pthLoad->AddNumRequests();

}

void SM_LoaderTile::slotRenderFinish()
{

    if(m_Lock.tryLock())
    {
        m_spMap.data()->setContent(m_Map,m_pCanvas->extent());
        m_Lock.unlock();
    }

}

void SM_LoaderTile::InitCanvas()
{

    m_pCanvas->setDestinationCrs(QgsCoordinateReferenceSystem("epsg:4130"));
    m_pCanvas->freeze(true);
    m_pCanvas->setExtent(QgsRectangle(-180,-90,180,90));
}

void SM_LoaderTile::calculatePara(int& nLOD, int& nBlkXBegin, int& nBlkYBegin, int& nBlkXEnd, int& nBlkYEnd,int& nW,QgsPoint& ptOri)
{
    //获取范围
    double dLMin , dBMin, dLMax, dBMax;
    QgsRectangle extent  = m_pCanvas->extent();

    dLMax = extent.xMaximum(); dLMin = extent.xMinimum();
    dBMax = extent.yMaximum(); dBMin = extent.yMinimum();

    if (dLMax >  180) dLMax =  180;
    if (dLMin < -180) dLMin = -180;
    if (dBMax >   90) dBMax =   90;
    if (dBMin <  -90) dBMin =  -90;

    //获取合适的LOD
    nLOD = GetFitLod(qAbs(extent.xMaximum() - extent.xMinimum()), m_pCanvas->mapSettings().outputSize().width());
    if (nLOD  < 0) return;

    //获取起止块号
    GetBlkNoXYBeginEnd(s_ConfigPar, nLOD, dLMin, dBMin, dLMax, dBMax, nBlkXBegin, nBlkYBegin, nBlkXEnd, nBlkYEnd);

    //计算所需标准块地理范围最值
    double dBlkXMin, dBlkYMin, dBlkXMax, dBlkYMax;
    double dX0, dY0, dX1, dY1;
    GetBlkBound(s_ConfigPar,nLOD,nBlkXBegin,nBlkYBegin,dX0,dY0,dX1,dY1);//左下角
    dBlkXMin = dX0; dBlkYMin = dY0;
    GetBlkBound(s_ConfigPar,nLOD,nBlkXEnd,nBlkYEnd,dX0,dY0,dX1,dY1);//右上角
    dBlkXMax = dX1; dBlkYMax = dY1;


    //计算绘制的设备坐标（左下角）
    ptOri = m_pCanvas->getCoordinateTransform()->transform(dBlkXMin,dBlkYMin);

    //计算实际渲染地图大小
    nW = (dBlkXMax - dBlkXMin)/m_pCanvas->mapUnitsPerPixel()/(nBlkXEnd - nBlkXBegin + 1);

    //构造最终的地图
    m_Map = QImage(m_pCanvas->size(),QImage::Format_ARGB32);


}

void SM_LoaderTile::LoadLocal()
{
    int nW = -1;
    QgsPoint ptOri;
    int nLOD = -1,nBlkXBegin = -1, nBlkYBegin = -1, nBlkXEnd = -1, nBlkYEnd = -1;

    calculatePara(nLOD,nBlkXBegin,nBlkYBegin,nBlkXEnd,nBlkYEnd,nW,ptOri);
    if (nLOD  < 0 || nBlkXBegin < 0 || nBlkYBegin < 0 || nBlkXEnd < 0 || nBlkYEnd < 0) return;

     QPainter painter(&m_Map);

     //遍历获取瓦片并组合为最终的地图
     int nXOri = ptOri.x(), nYOri = ptOri.y() - nW; //绘制原点

     for(int nIndexY = nBlkYBegin ; nIndexY <= nBlkYEnd ; nIndexY++)
     {

         for(int nIndeX = nBlkXBegin ; nIndeX <= nBlkXEnd ; nIndeX++)
         {
             QImage imgTile;
             FindBlk(imgTile,m_qstrPath,nLOD,nIndeX,nIndexY);
             imgTile = imgTile.scaled(nW,nW);
             painter.drawImage(nXOri,nYOri,imgTile);
             nXOri += nW;
         }

         nXOri = ptOri.x();
         nYOri -= nW;
     }


}


void SM_LoaderTile::RealRender()
{
    m_Lock.lock();
    int nW = -1;
    QgsPoint ptOri;
    int nLOD = -1,nBlkXBegin = -1, nBlkYBegin = -1, nBlkXEnd = -1, nBlkYEnd = -1;

    calculatePara(nLOD,nBlkXBegin,nBlkYBegin,nBlkXEnd,nBlkYEnd,nW,ptOri);
    if (nLOD  < 0 || nBlkXBegin < 0 || nBlkYBegin < 0 || nBlkXEnd < 0 || nBlkYEnd < 0) return;

    QPainter painter(&m_Map);

    //遍历获取瓦片并组合为最终的地图
    int nXOri = ptOri.x(), nYOri = ptOri.y() - nW; //绘制原点

    for(int nIndexY = nBlkYBegin ; nIndexY <= nBlkYEnd ; nIndexY++)
    {

        for(int nIndeX = nBlkXBegin ; nIndeX <= nBlkXEnd ; nIndeX++)
        {
            QImage imgTile;
            if (!FindBlk(imgTile,m_qstrSearchPath,nLOD,nIndeX,nIndexY))
            {
                unsigned char* pimgbyte = m_pTool->RenderMap( nLOD, nIndeX, nIndexY ); //渲染
                imgTile = QImage(pimgbyte,m_nSzie, m_nSzie, QImage::Format_ARGB32 );
                imgTile = QGLWidget::convertToGLFormat(imgTile);//转换为QImage的格式

            }
            imgTile = imgTile.scaled(nW,nW);
            painter.drawImage(nXOri,nYOri,imgTile);

            nXOri += nW;

        }

        nXOri = ptOri.x();
        nYOri -= nW;
    }
    m_Lock.unlock();
    emit sigRenderFinish();

}

