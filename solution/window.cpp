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
  createPageArea();
  createHomePage();
  createSecondTestPage();

  setMinimumWidth(MIN_WINDOW_WIDTH);
  setWindowTitle("Water Sample Tool");
}

void WaterSampleWindow::createMenuBar()
{
  // create mac friendly menubar
  QMenuBar *menuBar = new QMenuBar(nullptr);
  QMenu *fileMenu = menuBar->addMenu("File");

  QAction *openAct = new QAction("Open CSV", this);
  openAct->setShortcuts(QKeySequence::Open);
  openAct->setStatusTip(tr("Open a CSV dataset"));
  connect(openAct, &QAction::triggered, this, &WaterSampleWindow::openCSV);

  QAction* aboutAct = new QAction("About", this);
  aboutAct->setShortcuts(QKeySequence::HelpContents);
  aboutAct->setStatusTip(tr("About this app"));
  connect(aboutAct, &QAction::triggered, this, &WaterSampleWindow::about);

  QAction *exitAct = new QAction("Exit", this);
  exitAct->setShortcuts(QKeySequence::Close);
  connect(exitAct, &QAction::triggered, this, &WaterSampleWindow::close);
  fileMenu->addAction(openAct);
  fileMenu->addAction(aboutAct);
  fileMenu->addAction(exitAct);

  this->setMenuBar(menuBar);
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
void WaterSampleWindow::createPageArea()
{
  scrollArea = new QScrollArea();
  scrollArea->setWidgetResizable(true);
  mainWindowLayout->addWidget(scrollArea);

  pagesStackedWidget = new QStackedWidget();
  scrollArea->setWidget(pagesStackedWidget);
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
