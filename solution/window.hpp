#pragma once

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QChartView>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QStackedWidget>
#include <QPalette>

#include "table_model.hpp"
#include "pollutant_line_chart.hpp"
#include "navbar.hpp"
#include "text_components.hpp"

class QString;
class QComboBox;
class QLabel;
class QPushButton;
class QTableView;
class StatsDialog;

class WaterSampleWindow: public QMainWindow
{
  Q_OBJECT

  public:
    WaterSampleWindow();

  private:
    QWidget* mainWindowContainer;
    QVBoxLayout* mainWindowLayout;
    NavBar* navBar;
    QTabWidget* tabSwitcher;
    QScrollArea* scrollArea;
    QStackedWidget* pagesStackedWidget;
    TextComponents* textComponents;
    QTableView* table;

    WaterSampleTableModel model;

    PollutantTrendLineChart* chart;
    QChartView* chartView;
    QSortFilterProxyModel* proxyModel;

    void createMenuBar();
    void createMainLayout();
    void createNavBar();
    void createPageArea();
    void addPage(QWidget* page, const QString& label);
    void createHomePage();
    void createDataPage();
    void createPollutantOverviewPage();
    void createPersistentOrganicPollutantsPage();
    void createEnvironmentalLitterIndicatorsPage();
    void createFluorinatedCompoundsPage();
    void createComplianceDashboardPage();


  private slots:
    void openCSV();
    void about();
};
