#include "pollutant_line_chart.hpp"

PollutantTrendLineSeries::PollutantTrendLineSeries(
    const QString& pollutant,
    WaterSampleTableModel* model
)
{
    timeSinceEpochProxyModel = new WaterSampleTableTimeSinceEpochProxy(this);
    timeSinceEpochProxyModel->setSourceModel(model);

    filterProxyModel = new QSortFilterProxyModel(this);
    filterProxyModel->setSourceModel(timeSinceEpochProxyModel);
    filterProxyModel->setFilterFixedString(pollutant);
    filterProxyModel->setFilterKeyColumn(5);
    filterProxyModel->sort(4);

    mapper = new QVXYModelMapper(this);
    mapper->setModel(filterProxyModel);
    mapper->setSeries(this);
    mapper->setXColumn(4);
    mapper->setYColumn(9);
}


PollutantTrendLineChart::PollutantTrendLineChart(
    const QString& pollutant,
    WaterSampleTableModel* model,
    QGraphicsItem *parent
): QChart(parent)
{
    legend()->hide();
    setAnimationOptions(QChart::AllAnimations);
    pollutant_series = new PollutantTrendLineSeries(pollutant, model);
    addSeries(pollutant_series);
    setAxes();
}

void PollutantTrendLineChart::setAxes()
{
    for (auto axis : axes()) {
        removeAxis(axis);
    }

    auto axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Date");
    addAxis(axisX, Qt::AlignBottom);
    pollutant_series->attachAxis(axisX);

    auto axisY = new QValueAxis;
    axisY->setLabelFormat("%.2f");
    axisY->setTitleText("Result");
    addAxis(axisY, Qt::AlignLeft);
    pollutant_series->attachAxis(axisY);
}