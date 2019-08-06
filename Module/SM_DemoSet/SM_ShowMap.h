//**************************************************************************
// 文件：  SM_ShowMap.h
// 描述：  用于加载数据并显示地图
// 作者：  w_s_y
// 首次创建时间：2019-8-1
// 最近更新时间：2019-8-5
// 更新内容：优化坐标显示（依据不同比例显示不同精度的坐标）
//**************************************************************************

#ifndef SM_SHOWMAP_H
#define SM_SHOWMAP_H
#include <QString>
#include <QWidget>
#include <QObject>

#include <sm_demoset_global.h>

class SM_LoaderTile;
class QgsMapCanvas;
class QgsPoint;

struct SM_Point
{
    double m_dx,m_dy;
};
class SM_DEMOSETSHARED_EXPORT SM_ShowMap : public QObject
{

    Q_OBJECT
public:
    /**
     * @brief 数据类型，后期会优化掉
     */
    enum Datatype
    {
        VECTOR,
        RASTER

    };

    SM_ShowMap(const QString& qstrFilePath, bool bRender = false, QWidget* parent = NULL);
    ~SM_ShowMap();

    QgsMapCanvas& GetCanvas(){ if(m_pCanvas) return  *m_pCanvas;}

    /**
     * @brief 启用瓦片加载器
     * @param bTileRender
     */
    void EnableTilesLoader(bool bTileRender);

    void SetTileSize(int nSize);

    /**
     * @brief 设置要搜索的硬盘瓦片路径（只有启用瓦片加载时才可用）
     */
    void SetSearchPath(const QString& qstrPath);

    void SetDataType(Datatype Type) {m_enumType = Type;}

    void ShowMap();

signals:

    /**
     * @brief 发送地图坐标
     * @param pt
     */
    void sigXY(const SM_Point& pt);

private slots:

    /**
     * @brief 用于发送地图坐标
     * @param p
     */
    void slotShowXY( const QgsPoint &p);

    /**
     * @brief 更新坐标精度
     * @param dPre
     */
    void slotUpdatePrecision();
private:

    /**
     * @brief 初始化
     * @param parent
     */
    void Init(QWidget* parent);

    /**
     * @brief 加载地图
     */
    void LoadMap();

    /**
     * @brief 加载数据文件（如*.shp,*.mif等）
     */
    void LoadDataFile();

    /**
     * @brief 加载qgis工程
     */
    void LoadPro();

    /**
     * @brief 加载瓦片
     */
    void LoadTile();

private:

    QgsMapCanvas* m_pCanvas;

    /**
     * @brief 瓦片加载器
     */
    SM_LoaderTile* m_pLoader;

    /**
     * @brief 用于显示坐标
     */
    SM_Point m_pt;

    /**
     * @brief 文件路径
     */
    QString m_qstrFilePath;

    Datatype m_enumType;

    /**
     * @brief 是否启用瓦片渲染
     */
    bool m_bLoadTiles;

    /**
     * @brief 坐标精度
     */
    unsigned int m_unPrecision;

};

#endif // SM_SHOWMAP_H
