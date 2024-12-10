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
  createPages();
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

void WaterSampleWindow::addPage(Page* page, const QString& label)
{
  navBar->addTab(pagesStackedWidget, label);
  pagesStackedWidget->addWidget(page);
  connect(this, SIGNAL(newCSVLoaded()), page, SLOT(modelUpdated()));
}

void WaterSampleWindow::createPages()
{
  addPage(new HomePage(&model), "Home");
  addPage(new PollutantOverviewPage(&model), "Pollutant Overview Page");
  addPage(new PersistentOrganicPollutantsPage(&model), "Persistent Organic Pollutants Page");
  addPage(new EnvironmentalLitterIndicatorsPage(&model), "Environmental Litter Indicators Page");
  addPage(new FluorinatedCompoundsPage(&model), "Fluorinated Compounds Page");
  addPage(new ComplianceDashboardPage(&model), "Compliance Dashboard Page");
  addPage(new DataPage(&model), "Data Page");
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

  newCSVLoaded();
}

void WaterSampleWindow::about()
{
  QMessageBox::about(this, "About Water Sample Tool",
    "Water Sample Tool displays and analyzes water sample data loaded from "
    "a CSV file");
}