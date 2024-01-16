#include "Qt_SimplePaint.h"
#include <QtWidgets/QApplication>

#include <QFile>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    // Set the app style sheet
    QFile styleSheetFile("./Adaptic.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);

    Qt_SimplePaint w;
    w.show();
    return a.exec();
}
