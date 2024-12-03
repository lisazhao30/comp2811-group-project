#include "line_chart.hpp"

PollutantTrendLineSeries::PollutantTrendLineSeries(
    const QString& pollutant,
    WaterSampleTableModel& model
)
{
    monthDayProxyModel = new WaterSampleTableMonthDayProxy(this);
    monthDayProxyModel->setSourceModel(&model);

    filterProxyModel = new QSortFilterProxyModel(this);
    filterProxyModel->setSourceModel(monthDayProxyModel);
    filterProxyModel->setFilterFixedString(pollutant);
    filterProxyModel->setFilterKeyColumn(6);

    mapper = new QVXYModelMapper(this);
    mapper->setXColumn(5);
    mapper->setYColumn(9);

    mapper->setModel(filterProxyModel);
    mapper->setSeries(this);
}
