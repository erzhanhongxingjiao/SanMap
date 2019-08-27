//**************************************************************************
// 文件：  SM_BarTool.h
// 描述：  自定义工具栏
// 作者：  w_s_y
// 最近更新时间：  2019-8-26
// 更新内容：编写第一个版本
//**************************************************************************

#ifndef SM_BARTOOL_H
#define SM_BARTOOL_H

#include <QWidget>
class QHBoxLayout;
class QVBoxLayout;
class SM_BarTool : public QWidget
{
    Q_OBJECT
public:
    explicit SM_BarTool(QWidget *parent = 0);

signals:

public slots:

private:
    QVBoxLayout* m_pVLay;
    QHBoxLayout* m_pHLay;



};

#endif // SM_BARTOOL_H
