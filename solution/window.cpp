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
  model.updateFromFile(QCoreApplication::applicationDirPath() + "/data/data_small.db");

  createMenuBar();
  createMainLayout();
  createNavBar();
  createPageArea();
  createPages();
  setMinimumWidth(MIN_WINDOW_WIDTH);
  setWindowTitle("Water Quality Monitor");
}

void WaterSampleWindow::createMenuBar()
{
  // create mac friendly menubar
  QMenuBar *menuBar = new QMenuBar();
  QMenu *fileMenu = menuBar->addMenu("File");

  QAction *openAct = new QAction("Open DB", this);
  openAct->setShortcuts(QKeySequence::Open);
  openAct->setStatusTip(tr("Open a SQLite DB"));
  connect(openAct, &QAction::triggered, this, &WaterSampleWindow::openDb);

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
  connect(this, SIGNAL(newDbLoaded()), page, SLOT(modelUpdated()));
}

void WaterSampleWindow::createPages()
{
  addPage(new HomePage(&model), "Home");
  addPage(new PollutantOverviewPage(&model), "Pollutant Overview");
  addPage(new PersistentOrganicPollutantsPage(&model), "Persistent Organic Pollutants");
  addPage(new EnvironmentalLitterIndicatorsPage(&model), "Environmental Litter Indicators");
  addPage(new FluorinatedCompoundsPage(&model), "Fluorinated Compounds");
  addPage(new ComplianceDashboardPage(&model), "Compliance Dashboard");
  addPage(new DataPage(&model), "Data Page");
}

void WaterSampleWindow::openDb()
{
  QString filename = QFileDialog::getOpenFileName(
    this, "Data Location", ".",
    "DB files (*.db)");

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
    QMessageBox::critical(this, "DB File Error", error.what());
    return;
  }

  newDbLoaded();
}

void WaterSampleWindow::about()
{
  QMessageBox::about(this, "About Water Quality Monitor",
    "Water Quality Monitor displays and analyzes water sample data from a SQL Database");
}
