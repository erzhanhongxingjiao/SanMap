#include "SM_WndMain.h"
#include <QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //设置文件编码
    QTextCodec* code= QTextCodec::codecForName ( "GBK" );
    QTextCodec::setCodecForCStrings(code);
    QTextCodec::setCodecForTr(code);
    QTextCodec::setCodecForLocale(code);

    SM_WndMain w;
    w.show();
    w.showMaximized();
    return a.exec();
}
