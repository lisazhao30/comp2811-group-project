// COMP2811 Coursework 2 sample solution: main window

#pragma once

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QChartView>
#include "table_model.hpp"
#include "pollutant_line_chart.hpp"

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
    WaterSampleTableModel model;
    PollutantTrendLineChart* chart;
    QChartView* chartView;
    QPushButton* loadButton;

    void createMainWidget();
    void createToolBar();
    void createButtons();


  private slots:
    void openCSV();
    void displayStats();
    void about();
};
