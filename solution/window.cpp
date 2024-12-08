#include <QtWidgets>
#include <QChart>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QTabWidget>
#include <stdexcept>
#include <iostream>
#include "window.hpp"

#define MIN_WINDOW_WIDTH 620

WaterSampleWindow::WaterSampleWindow(): QMainWindow()
{
  createMenuBar();
  createMainLayout();
  createNavBar();
  createScrollArea();
  createPageLayout();
  createHomePage();
  createSecondTestPage();

  setMinimumWidth(MIN_WINDOW_WIDTH);
  setWindowTitle("Water Sample Tool");
}

void WaterSampleWindow::createMenuBar()
{
  QAction* openAct = menuBar()->addAction("Open CSV", this, SLOT(openCSV()));
  openAct->setShortcuts(QKeySequence::Open);
  openAct->setStatusTip(tr("Open a CSV dataset"));

  QAction* aboutAct = menuBar()->addAction("About", this, SLOT(about()));
  aboutAct->setShortcuts(QKeySequence::HelpContents);
  aboutAct->setStatusTip(tr("About this app"));

  QAction* exitAct = menuBar()->addAction("Exit", this, SLOT(close()));
  exitAct->setShortcuts(QKeySequence::Close);
}

// Create the central widget, and layout for nav bar and scroll area
void WaterSampleWindow::createMainLayout()
{
  mainWindowContainer = new QWidget(this);
  mainWindowLayout = new QVBoxLayout();
  mainWindowContainer->setLayout(mainWindowLayout);
  setCentralWidget(mainWindowContainer);
}

void WaterSampleWindow::createNavBar()
{
  navBar = new NavBar();
  mainWindowLayout->addWidget(navBar);
}

// Create a scroll area for the main page content, and a container widget
void WaterSampleWindow::createScrollArea()
{
  scrollArea = new QScrollArea();
  scrollArea->setWidgetResizable(true);
  mainWindowLayout->addWidget(scrollArea);

  scrollAreaContainer = new QWidget(scrollArea);
  scrollAreaContainer->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  scrollArea->setWidget(scrollAreaContainer);
}

// Create a layout for inside the scroll area container,
// and a stacked widget to hold the pages
void WaterSampleWindow::createPageLayout()
{
  pageLayout = new QVBoxLayout(scrollAreaContainer);
  scrollAreaContainer->setLayout(pageLayout);
  
  pagesStackedWidget = new QStackedWidget();
  pageLayout->addWidget(pagesStackedWidget);
}

void WaterSampleWindow::addPage(QWidget* page, const QString& label)
{
  navBar->addTab(pagesStackedWidget, label);
  pagesStackedWidget->addWidget(page);
}

void WaterSampleWindow::createHomePage()
{
  chart = new PollutantTrendLineChart("Nitrate-N", &model);
  chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);
  addPage(chartView, "Home");
}

void WaterSampleWindow::createSecondTestPage()
{
  QWidget* page = new QWidget();
  QVBoxLayout* layout = new QVBoxLayout(page);
  QLabel* label = new QLabel("Second Test Page");
  layout->addWidget(label);
  addPage(page, "Second Test Page");
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


void WaterSampleWindow::about()
{
  QMessageBox::about(this, "About Water Sample Tool",
    "Water Sample Tool displays and analyzes water sample data loaded from "
    "a CSV file");
}
