#include "SM_BarTool.h"
#include <QtGui>
SM_BarTool::SM_BarTool(QWidget *parent) : QWidget(parent),
  m_pHLay(NULL),
  m_pVLay(NULL)
{
    m_pVLay = new QVBoxLayout(this);
}
