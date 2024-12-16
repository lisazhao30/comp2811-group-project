#include <QtWidgets>
#include "window.hpp"

int main(int argc, char* argv[])
{
  qputenv("QT_QPA_PLATFORM", "windows:darkmode=0");
  QApplication app(argc, argv);

  WaterSampleWindow window;
  window.show();

  return app.exec();
}
