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

#include "pages/page.hpp"
#include "pages/home.hpp"
#include "pages/pollutant_overview.hpp"
#include "pages/persistent_organic_pollutants.hpp"
#include "pages/environmental_litter_indicators.hpp"
#include "pages/fluorinated_compounds.hpp"
#include "pages/compliance_dashboard.hpp"
#include "pages/data_page.hpp"

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

    WaterSampleTableModel model;
    QSortFilterProxyModel* proxyModel;

    void createMenuBar();
    void createMainLayout();
    void createNavBar();
    void createPageArea();
    void addPage(Page* page, const QString& label);
    void createHomePage();
    void createDataPage();
    void createPollutantOverviewPage();
    void createPersistentOrganicPollutantsPage();
    void createEnvironmentalLitterIndicatorsPage();
    void createFluorinatedCompoundsPage();
    void createComplianceDashboardPage();

  signals:
    void newCSVLoaded();

  private slots:
    void openCSV();
    void about();
};
