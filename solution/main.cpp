#include <QtWidgets>
#include "window.hpp"

int main(int argc, char* argv[])
{
#if defined(Q_OS_WIN)
  qputenv("QT_QPA_PLATFORM", "windows:darkmode=0");
#elif defined(Q_OS_MAC)
  qputenv("QT_QPA_PLATFORM", "cocoa");
#endif
  QApplication app(argc, argv);

  WaterSampleWindow window;
  window.show();

  return app.exec();
}
