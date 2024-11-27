#include <QtWidgets>
#include <stdexcept>
#include <iostream>
#include "window.hpp"

static const int MIN_WIDTH = 620;


WaterSampleWindow::WaterSampleWindow(): QMainWindow()
{
  createMainWidget();
  createButtons();
  createToolBar();

  setMinimumWidth(MIN_WIDTH);
  setWindowTitle("Water Sample Tool");
}


void WaterSampleWindow::createMainWidget()
{
  table = new QTableView();
  table->setModel(&model);

  QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
  table->setFont(tableFont);

  setCentralWidget(table);
}

void WaterSampleWindow::createButtons()
{
  loadButton = new QPushButton("Load");

  connect(loadButton, SIGNAL(clicked()), this, SLOT(openCSV()));
}

void WaterSampleWindow::createToolBar()
{
  QToolBar* toolBar = new QToolBar();
  toolBar->addWidget(loadButton);
  addToolBar(Qt::LeftToolBarArea, toolBar);
}


void WaterSampleWindow::openCSV()
{
  QString filename = QFileDialog::getOpenFileName(
    this, "Data Location", ".",
    "CSV files (*.csv)");

  if (filename.length() == 0) {
    QMessageBox::critical(this, "Data Location Error",
      "No data location specified!"
    );
    return;
  }

  try {
    model.updateFromFile(filename);
  }
  catch (const std::exception& error) {
    QMessageBox::critical(this, "CSV File Error", error.what());
    return;
  }

  table->resizeColumnsToContents();

  // TODO: call function to update stats
}


void WaterSampleWindow::displayStats()
{
  if (model.hasData()) {
    // TODO: display stats
  }
}


void WaterSampleWindow::about()
{
  QMessageBox::about(this, "About Water Sample Tool",
    "Water Sample Tool displays and analyzes water sample data loaded from"
    "a CSV file");
}
