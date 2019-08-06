//**************************************************************************
// 文件：  SM_Thread.h
// 描述：  SanMap线程，目前仅作瓦片渲染线程
// 作者：  w_s_y
// 最近更新时间：  2019-8-3
// 更新内容：编写第一个版本
//**************************************************************************

#ifndef SM_THREAD_H
#define SM_THREAD_H
#include <QThread>
#include <QMutex>
class SM_LoaderTile;
class SM_Thread : public QThread
{
public:
    SM_Thread();
    void SetTileLoader(SM_LoaderTile* pLoader){m_pLoader = pLoader;}

    /**
     * @brief 地图范围改变时需要调用，目的是保证地图为最新
     */
    void AddNumRequests(){m_nNumReq += 1;}

    /**
     * @brief 取消线程
     */
    void Cancel(){m_bCancel = true;}

protected:

    void run();

private:
    SM_LoaderTile* m_pLoader;

    bool m_bCancel;

    /**
     * @brief 请求数
     */
    int m_nNumReq;
};

#endif // SM_THREAD_H
