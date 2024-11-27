// COMP2811 Coursework 2 sample solution: main window

#pragma once

#include <QMainWindow>
#include "model.hpp"

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
    void createMainWidget();
    void createToolBar();
    void createButtons();

    WaterSampleModel model;          // data model used by table
    QTableView* table;         // table of water sample data
    QPushButton* loadButton;   // button to load a new CSV file

  private slots:
    void openCSV();
    void displayStats();
    void about();
};
