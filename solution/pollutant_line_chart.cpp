#include "pollutant_line_chart.hpp"

PollutantTrendLineSeries::PollutantTrendLineSeries(
    const QString& pollutant,
    QAbstractItemModel* model,
    QObject *parent
    ): QLineSeries(parent)
{
    timeSinceEpochProxyModel = new WaterSampleTableTimeSinceEpochProxy(this);
    timeSinceEpochProxyModel->setSourceModel(model);

    filterProxyModel = new QSortFilterProxyModel(this);
    filterProxyModel->setSourceModel(timeSinceEpochProxyModel);
    filterProxyModel->setFilterRegularExpression('^' + pollutant + '$');
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
    QAbstractItemModel* model,
    QGraphicsItem *parent
): QChart(parent)
{
    legend()->hide();
    setAnimationOptions(QChart::AllAnimations);
    pollutant_series = QList<PollutantTrendLineSeries*>();
    pollutant_series.append(new PollutantTrendLineSeries(pollutant, model, this));
    addSeries(pollutant_series.first());
    setAxes();
}

PollutantTrendLineChart::PollutantTrendLineChart(
    QList<QString> pollutants,
    QAbstractItemModel* model,
    QGraphicsItem *parent
    ): QChart(parent)
{
    legend()->hide();
    setAnimationOptions(QChart::AllAnimations);

    pollutant_series = QList<PollutantTrendLineSeries*>();
    for (auto pollutant : pollutants) {
        auto series = new PollutantTrendLineSeries(pollutant, model, this);
        addSeries(series);
        pollutant_series.append(series);
    }

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

    auto axisY = new QValueAxis;
    axisY->setLabelFormat("%.2f");
    axisY->setTitleText("Result");
    addAxis(axisY, Qt::AlignLeft);

    for (auto series : pollutant_series) {
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }
}
