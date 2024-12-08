#include <QtWidgets>
#include <QChart>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QTabWidget>
#include <stdexcept>
#include <iostream>
#include "window.hpp"

#define MIN_WINDOW_WIDTH 1200

WaterSampleWindow::WaterSampleWindow(): QMainWindow()
{
  createMenuBar();
  createMainLayout();
  createNavBar();
  createPageArea();
  createHomePage();
  createPollutantOverviewPage();
  createPersistentOrganicPollutantsPage();
  createEnvironmentalLitterIndicatorsPage();
  createFluorinatedCompoundsPage();
  createComplianceDashboardPage();
  createDataPage();

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

  // set background colour
  QPalette pal = QPalette();
  pal.setColor(QPalette::Window, QColor("#FAF5EB"));
  mainWindowContainer->setAutoFillBackground(true); 
  mainWindowContainer->setPalette(pal);

  // create layout box
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

// pages for the application
void WaterSampleWindow::createHomePage()
{
  // create page layout
  QWidget* page = new QWidget();
  QVBoxLayout* layout = new QVBoxLayout(page);

  // add text
  TextComponents* textComponents = new TextComponents();
  textComponents->addHeaderText("Spot the Trends, Shape the Future:\nWater Quality Insights at Your Fingertips");
  layout->addWidget(textComponents);

  // add chart
  chart = new PollutantTrendLineChart("Nitrate-N", &model);
  chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);
  layout->addWidget(chartView);

  addPage(page, "Home");
}

void WaterSampleWindow::createPollutantOverviewPage()
{
  QWidget* page = new QWidget();
  QVBoxLayout* layout = new QVBoxLayout(page);
  
  // add text
  TextComponents* textComponents = new TextComponents();
  textComponents->addHeader2Text("Pollutant Insights: Trends, Compliance, and Safety at a Glance");
  layout->addWidget(textComponents);

  addPage(page, "Pollutant Overview Page");
}

void WaterSampleWindow::createPersistentOrganicPollutantsPage()
{
  QWidget* page = new QWidget();
  QVBoxLayout* layout = new QVBoxLayout(page);

  // add text
  TextComponents* textComponents = new TextComponents();
  textComponents->addHeader2Text("Persistent Organic Pollutants:\nTracking Trends, Risks, and Compliance");
  layout->addWidget(textComponents);

  addPage(page, "Persistent Organic Pollutants Page");
}

void WaterSampleWindow::createEnvironmentalLitterIndicatorsPage()
{
  QWidget* page = new QWidget();
  QVBoxLayout* layout = new QVBoxLayout(page);
  
  // add text
  TextComponents* textComponents = new TextComponents();
  textComponents->addHeader2Text("Environmental Litter Indicators: Tracking Pollution in Waterways");
  layout->addWidget(textComponents);

  addPage(page, "Environmental Litter Indicators Page");
}

void WaterSampleWindow::createFluorinatedCompoundsPage()
{
  QWidget* page = new QWidget();
  QVBoxLayout* layout = new QVBoxLayout(page);
  
  // add text
  TextComponents* textComponents = new TextComponents();
  textComponents->addHeader2Text("Fluorinated Compounds:\nMonitoring PFAS Levels and Environmental Impact");
  layout->addWidget(textComponents);

  addPage(page, "Fluorinated Compounds Page");
}

void WaterSampleWindow::createComplianceDashboardPage()
{
  QWidget* page = new QWidget();
  QVBoxLayout* layout = new QVBoxLayout(page);

  // add text
  TextComponents* textComponents = new TextComponents();
  textComponents->addHeader2Text("Compliance Dashboard:\nTracking Safety Standards Across Pollutants");
  layout->addWidget(textComponents);

  addPage(page, "Compliance Dashboard Page");
}

void WaterSampleWindow::createDataPage()
{
  QWidget* page = new QWidget();
  QVBoxLayout* layout = new QVBoxLayout(page);
  
  // add text
  TextComponents* textComponents = new TextComponents();
  textComponents->addHeader2Text("Data Page");
  layout->addWidget(textComponents);

  // add table
  table = new QTableView();

  proxyModel = new QSortFilterProxyModel(this);
  proxyModel->setSourceModel(&model);
  proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

  WaterSampleTableTimeSinceEpochProxy* monthDayProxyModel = new WaterSampleTableTimeSinceEpochProxy(this);
  monthDayProxyModel->setSourceModel(proxyModel);

  table->setModel(monthDayProxyModel);

  QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
  table->setFont(tableFont);
  layout->addWidget(table);

  addPage(page, "Data Page");
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