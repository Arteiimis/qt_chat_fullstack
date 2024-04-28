#include "mainwindow.h"
#include "qapplication.h"
#include "qcontainerfwd.h"
#include "qdebug.h"
#include "qimage.h"
#include "qlatin1stringview.h"
#include <QApplication>
#include <spdlog/spdlog.h>
#include <QFile>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    QString qssPath = ":/rcs/stylesheet.qss";
    QFile   qssFile(qssPath);
    if ( qssFile.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        spdlog::info("Open qss file successfully");
        QString qss = QLatin1String(qssFile.readAll());
        a.setStyleSheet(qss);
        qssFile.close();
    } else {
        spdlog::error("Failed to open qss file");
    }

    MainWindow w;
    w.show();

    return a.exec();
}
