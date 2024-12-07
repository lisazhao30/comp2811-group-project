#include <QtWidgets>
#include <QChart>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <stdexcept>
#include <iostream>
#include "window.hpp"

#define MIN_WINDOW_WIDTH 620


WaterSampleWindow::WaterSampleWindow(): QMainWindow()
{
  createMainWidget();
  createButtons();
  createToolBar();
  setMinimumWidth(MIN_WINDOW_WIDTH);
  setWindowTitle("Water Sample Tool");
}


void WaterSampleWindow::createMainWidget()
{
  chart = new PollutantTrendLineChart("Nitrate-N", &model);
  chartView = new QChartView(chart, this);
  setCentralWidget(chartView);
}

void WaterSampleWindow::createButtons()
{
  loadButton = new QPushButton("Load");
  connect(loadButton, SIGNAL(clicked()), this, SLOT(openCSV()));
}

void WaterSampleWindow::createToolBar()
{
  QToolBar* toolBar = new QToolBar();

  loadButton = new QPushButton("Load");
  connect(loadButton, SIGNAL(clicked()), this, SLOT(openCSV()));

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

  auto series = chart->series().at(0);
  // Refreshes the chart, probably shouldn't need this, bug?
  chart->removeSeries(series);
  chart->addSeries(series);
  
  chart->setAxes();
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
