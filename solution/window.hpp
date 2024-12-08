#pragma once

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QChartView>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QStackedWidget>

#include "table_model.hpp"
#include "pollutant_line_chart.hpp"
#include "navbar.hpp"

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
    QWidget* scrollAreaContainer;
    QVBoxLayout* pageLayout;
    QStackedWidget* pagesStackedWidget;

    WaterSampleTableModel model;

    PollutantTrendLineChart* chart;
    QChartView* chartView;

    void createMenuBar();
    void createMainLayout();
    void createNavBar();
    void createScrollArea();
    void createPageLayout();
    void addPage(QWidget* page, const QString& label);
    void createHomePage();
    void createSecondTestPage();


  private slots:
    void openCSV();
    void about();
};
