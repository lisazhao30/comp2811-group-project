#include <QtWidgets>
#include <QChart>
#include <stdexcept>
#include <iostream>
#include "window.hpp"
#include "line_chart.hpp"

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
  table = new QTableView();

  proxyModel = new QSortFilterProxyModel(this);
  proxyModel->setSourceModel(&model);
  proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

  WaterSampleTableMonthDayProxy* monthDayProxyModel = new WaterSampleTableMonthDayProxy(this);
  monthDayProxyModel->setSourceModel(proxyModel);

  table->setModel(monthDayProxyModel);

  QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
  table->setFont(tableFont);

  auto chart = new QChart;
  chart->setAnimationOptions(QChart::AllAnimations);
  auto series = new PollutantTrendLineSeries("Nitrate-N", model);
  chart->addSeries(series);
  chart->createDefaultAxes();
  chartView = new QChartView(chart, this);
  setCentralWidget(chartView);

  //setCentralWidget(table);
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

  filterInput = new QLineEdit();
  filterInput->setPlaceholderText("Filter...");
  connect(filterInput, &QLineEdit::textChanged, this, &WaterSampleWindow::applyFilter);

  toolBar->addWidget(loadButton);
  toolBar->addWidget(filterInput);

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
  chartView->repaint();

  // TODO: call function to update stats
}


void WaterSampleWindow::displayStats()
{
  if (model.hasData()) {
    // TODO: display stats
  }
}

void WaterSampleWindow::applyFilter()
{
  QString filterText = filterInput->text();

  proxyModel->setFilterKeyColumn(-1);
  proxyModel->setFilterFixedString(filterText);
}

void WaterSampleWindow::about()
{
  QMessageBox::about(this, "About Water Sample Tool",
    "Water Sample Tool displays and analyzes water sample data loaded from"
    "a CSV file");
}
