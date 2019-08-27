#include "SM_ToolPlot.h"
#include <QtGui>
SM_ToolPlot::SM_ToolPlot(QWidget *parent) :
    QWidget(parent),
    m_pbtnPt(NULL),
    m_pbtnLine(NULL),
    m_pbtnPolygon(NULL)
{
    QVBoxLayout* pvLay = new QVBoxLayout(this);
    m_pbtnPt = new QPushButton("添加点");
    m_pbtnPt->resize(40,40);
    m_pbtnLine = new QPushButton("添加线");
    m_pbtnLine->resize(40,40);
    m_pbtnPolygon = new QPushButton("添加面");
    m_pbtnPolygon->resize(40,40);

    pvLay->addWidget(m_pbtnPt);
    pvLay->addWidget(m_pbtnLine);
    pvLay->addWidget(m_pbtnPolygon);

    resize(50,);


}

//void SM_ToolPlot::CreateBtn(const QString &name, QVBoxLayout* pLay)
//{

//}
