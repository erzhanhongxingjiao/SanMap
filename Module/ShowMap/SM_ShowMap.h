#ifndef SM_SHOWMAP_H
#define SM_SHOWMAP_H
#include <QString>
#include <QWidget>
#include <showmap_global.h>
class QgsMapCanvas;
class SHOWMAPSHARED_EXPORT SM_ShowMap
{

public:
    enum Datatype
    {
        VECTOR,
        RASTER

    };

    SM_ShowMap(const QString& qstrFilePath, Datatype Type, QWidget* parent = NULL);
    ~SM_ShowMap();

    QgsMapCanvas& GetCanvas(){ if(m_pCanvas) return  *m_pCanvas;}

    void ShowMap();

private:

    void Init();

    void LoadData();


    QgsMapCanvas* m_pCanvas;

    QString m_qstrFilePath;

    Datatype m_enumType;


};

#endif // SM_SHOWMAP_H
