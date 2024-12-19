#include <QtWidgets>
#include <QTabWidget>
#include <stdexcept>
#include <iostream>
#include "window.hpp"

#define MIN_WINDOW_WIDTH 1200

WaterSampleWindow::WaterSampleWindow(): QMainWindow()
{
    createLoadingPopup();

    loadingPopup->open();
    model.updateFromFile(QCoreApplication::applicationDirPath() + "/data/2024_small.db");
    loadingPopup->close();

    createMenuBar();
    createMainLayout();
    createNavBar();
    createPageArea();
    createPages();
    setMinimumWidth(MIN_WINDOW_WIDTH);
    setWindowTitle(tr("Water Quality Monitor"));
}

void WaterSampleWindow::createLoadingPopup() {
    loadingPopup = new QDialog(this);
    loadingPopup->setMinimumSize(300, 150);

    QVBoxLayout* dialogLayout = new QVBoxLayout();
    dialogLayout->setAlignment(Qt::AlignCenter);
    QLabel* text = new QLabel(tr("Loading Database..."));
    progressBar = new QProgressBar();
    progressBar->setRange(0, 100);
    dialogLayout->addWidget(text);
    dialogLayout->addWidget(progressBar);

    loadingPopup->setLayout(dialogLayout);

    connect(model.getDataset(), SIGNAL(updateLoadingProgress(int)), this, SLOT(updateDatabaseProgress(int)));
}

void WaterSampleWindow::updateDatabaseProgress(int percent) {
    progressBar->setValue(percent);
}

void WaterSampleWindow::createMenuBar()
{
    // create mac friendly menubar
    QMenuBar *menuBar = new QMenuBar();
    QMenu *fileMenu = menuBar->addMenu(tr("File"));

    QAction *openAct = new QAction(tr("Open DB"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a SQLite DB"));
    connect(openAct, &QAction::triggered, this, &WaterSampleWindow::openDb);

    QAction* aboutAct = new QAction(tr("About"), this);
    aboutAct->setShortcuts(QKeySequence::HelpContents);
    aboutAct->setStatusTip(tr("About this app"));
    connect(aboutAct, &QAction::triggered, this, &WaterSampleWindow::about);

    QAction *exitAct = new QAction(tr("Exit"), this);
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
    addPage(new HomePage(&model), tr("Home"));
    addPage(new PollutantOverviewPage(&model), tr("Pollutant Overview"));
    addPage(new PersistentOrganicPollutantsPage(&model), tr("Persistent Organic Pollutants"));
    addPage(new EnvironmentalLitterIndicatorsPage(&model), tr("Environmental Litter Indicators"));
    addPage(new FluorinatedCompoundsPage(&model), tr("Fluorinated Compounds"));
    addPage(new ComplianceDashboardPage(&model), tr("Compliance Dashboard"));
    addPage(new DataPage(&model), tr("Data"));
    addPage(new HelpPage(&model), tr("Help"));
}

void WaterSampleWindow::openDb()
{
    QString filename = QFileDialog::getOpenFileName(
        this, tr("Data Location"), ".",
        "DB files (*.db)");

    if (filename.length() == 0) {
        QMessageBox::critical(this, tr("Data Location Error"),
                              tr("No data location specified!")
                              );
        return;
    }

    try {
        loadingPopup->open();
        model.updateFromFile(filename);
        loadingPopup->close();
    }
    catch (const std::exception& error) {
        QMessageBox::critical(this, tr("DB File Error"), error.what());
        return;
    }

    newDbLoaded();
}

void WaterSampleWindow::about()
{
    QMessageBox::about(this, tr("About Water Quality Monitor"),
                       tr("Water Quality Monitor displays and analyzes water sample data from a SQL Database"));
}
