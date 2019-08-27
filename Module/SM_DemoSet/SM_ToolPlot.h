#ifndef SM_TOOLPLOT_H
#define SM_TOOLPLOT_H

#include <QWidget>
class QPushButton;
class SM_ToolPlot : public QWidget
{
    Q_OBJECT
public:
    explicit SM_ToolPlot(QWidget *parent = 0);

signals:

public slots:
private:
    //void CreateBtn(const QString& name, QVBoxLayout *pLay);
private:

    QPushButton* m_pbtnPt;
    QPushButton* m_pbtnLine;
    QPushButton* m_pbtnPolygon;

};

#endif // SM_TOOLPLOT_H
