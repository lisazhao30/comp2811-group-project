#include <QtWidgets>
#include <QTranslator>
#include <QLocale>
#include "window.hpp"

int main(int argc, char* argv[])
{
#if defined(Q_OS_WIN)
    qputenv("QT_QPA_PLATFORM", "windows:darkmode=0");
#elif defined(Q_OS_MAC)
    qputenv("QT_QPA_PLATFORM", "cocoa");
#endif
    QApplication app(argc, argv);

    QTranslator trn;
    if (trn.load(QLocale::system(), "watersampletool", "_", ":/i18n")) {
        app.installTranslator(&trn);
    }

    WaterSampleWindow window;
    window.show();

    return app.exec();
}
