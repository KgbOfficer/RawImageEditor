#include "Application.h"
#include <QFile>
#include <QTextStream>

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv)
{
    setApplicationName("RawImageEditor");
    // Load QSS
    QFile styleFile(":/styles.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream ts(&styleFile);
        setStyleSheet(ts.readAll());
    }
}