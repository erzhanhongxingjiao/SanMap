#include <QHBoxLayout>

#include "SM_WndMain.h"
#include "ui_SM_WndMain.h"


SM_WndMain::SM_WndMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SM_WndMain),
    m_pMap(NULL)
{
    ui->setupUi(this);

    Init();

    statusBar()->addWidget(ui->labXY);//地图坐标
}

SM_WndMain::~SM_WndMain()
{
    delete ui;
}

void SM_WndMain::slotShowXY(const SM_Point &p)
{
    ui->labXY->setText(QString("经度：%1 纬度：%2").arg(p.m_dx).arg(p.m_dy));
    ui->labXY->adjustSize();
}

void SM_WndMain::Init()
{
    //m_pMap = new SM_ShowMap("E:\\QGIS-2.18.5\\data\\shp\\World\\国家.shp",SM_ShowMap::VECTOR, this->centralWidget());
    m_pMap = new SM_ShowMap("E:/QGIS-2.18.5/data/MapTiles/Common",true,this->centralWidget());
    //m_pMap = new SM_ShowMap("E:\\QGIS-2.18.5\\data\\shp\\World\\国家.shp",false,this->centralWidget());
    //m_pMap = new SM_ShowMap("E:\\QGIS-2.18.5\\data\\MapTiles\\Common\\0\\0\\1.png",false,this->centralWidget());
    if (!m_pMap) return;

    connect(m_pMap,SIGNAL(sigXY(const SM_Point&)),this, SLOT(slotShowXY(const SM_Point&)));
    QHBoxLayout* pHLayout = new QHBoxLayout(this->centralWidget());
    pHLayout->addWidget((QWidget*)&m_pMap->GetCanvas());
    m_pMap->SetSearchPath("E:/QGIS-2.18.5/data/MapTiles/Common");
    m_pMap->SetDataType(SM_ShowMap::RASTER);
    m_pMap->ShowMap();
}
