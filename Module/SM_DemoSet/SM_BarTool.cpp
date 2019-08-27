
#include <QtGui>
#include "SM_BarTool.h"
#include "SM_ToolPlot.h"
SM_BarTool::SM_BarTool(QWidget *parent) : QWidget(parent),
    m_pPlot(NULL)
//  m_pbtnPlot(NULL)

{
    QPushButton* pbtnPlot = new QPushButton("标绘");
    pbtnPlot->resize(40,40);
    connect(pbtnPlot,SIGNAL(clicked(bool)),this,SLOT(slotShowPlot()));
    QVBoxLayout* pvLay = new QVBoxLayout(this);

    pvLay->addWidget(pbtnPlot);
    resize(50,pbtnPlot->height()+10);

}

void SM_BarTool::slotShowPlot()
{
    m_pPlot = new SM_ToolPlot(this->parent());

}
