//**************************************************************************
// 文件：  SM_WndMain.h(2019-8-1)
// 描述：  SanMap Demo主窗口
// 作者：  w_s_y
// 最近更新时间：  2019-8-1
// 更新内容：编写第一个版本
//**************************************************************************

#ifndef SM_WNDMAIN_H
#define SM_WNDMAIN_H

#include <QMainWindow>

#include <SM_ShowMap.h>
class SM_ShowMap;
class SM_Point;
namespace Ui {
class SM_WndMain;
}

class SM_WndMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit SM_WndMain(QWidget *parent = 0);
    ~SM_WndMain();

private slots:

    /**
     * @brief 显示地图坐标
     * @param p
     */
    void slotShowXY(const SM_Point &p);

private:
    void Init();
    //void InitControls();

private:
    Ui::SM_WndMain *ui;

    /**
     * @brief 地图加载显示类
     */
    SM_ShowMap* m_pMap;

};

#endif // SM_WNDMAIN_H
