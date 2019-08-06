//**************************************************************************
// 文件：  SM_LoaderTile.h
// 描述：  瓦片加载器，可加载本地瓦片或进行实时渲染
// 作者：  w_s_y
// 首次创建时间： 2019-8-1
// 最近更新时间： 2019-8-3
// 更新内容：修复画布更新时出现的全空白及卡死问题
//**************************************************************************
#ifndef SM_LOADERTILE_H
#define SM_LOADERTILE_H

#include <QObject>
#include <QSharedPointer>
#include <QMutex>

#include <qgsmapcanvas.h>
#include <IVBF_ToolSliceMap.h>

class QgsMapCanvas;
class SM_Thread;


class SM_LoaderTile : public QObject
{
    Q_OBJECT

public:
    explicit SM_LoaderTile(QgsMapCanvas* pCanvas, QString& path,QObject *parent = 0);
    ~SM_LoaderTile(); 

    void SetTileSize(int nSize){m_nSzie = nSize;}

    void SetSearchPath(const QString& qstrPath){ m_qstrSearchPath = qstrPath;}

    void Init();

signals:
    void sigRenderFinish();

public slots:
    void slotExtentChanged();

private slots:

    //渲染完成（主线程）
    void slotRenderFinish();


private:
    void InitCanvas();

    /**
     * @brief 计算绘制地图时的所需参数
     * @param nLOD
     * @param nBlkXBegin
     * @param nBlkYBegin
     * @param nBlkXEnd
     * @param nBlkYEnd
     * @param nW
     * @param ptOri
     */
    void calculatePara(int& nLOD, int& nBlkXBegin, int& nBlkYBegin, int& nBlkXEnd, int& nBlkYEnd,int& nW,QgsPoint& ptOri);

    /**
     * @brief 加载本地瓦片
     */
    void LoadLocal();

    /**
     * @brief 加载瓦片
     */
    void RealRender();

    //查找硬盘瓦片
    bool FindBlk(QImage& imgTile,QString& strSavePath, int nLOD, int nBlkX, int nBlkY)
    {
        //判断文件是否存在
        QString strBlkPath=strSavePath+ "/" +QString::number(nLOD, 10)+"/"+QString::number(nBlkY, 10)+"/"+
                QString::number(nBlkX, 10)+".png";
        QFile MapBlk(strBlkPath);
        if(MapBlk.exists())
        {
            imgTile = QImage(strBlkPath);
//            static int ik = 0;
//            imgTile.save(QString("E:/temp/test/%1.png").arg(ik));
//            ik++;
            return true;
        }
        return false;
    }

private:
    QgsMapCanvas* m_pCanvas;

    /**
     * @brief 切图工具
     */
    IVBF_ToolSliceMap* m_pTool;


    QSharedPointer<QgsMapCanvasMap> m_spMap;

    SM_Thread* m_pthLoad;

    friend class SM_Thread;

    /**
     * @brief 最终显示的地图
     */
    QImage m_Map;

    QMutex m_Lock;

    /**
     * @brief 瓦片大小
     */
    int m_nSzie;

    /**
     * @brief 文件夹或qgis工程文件
     */
    QString m_qstrPath;

    /**
     * @brief 是否从本地加载
     */
    bool m_bLoacal;

    /**
     * @brief 硬盘瓦片搜索路径
     */
    QString m_qstrSearchPath;

};

#endif // SM_LOADERTILE_H
