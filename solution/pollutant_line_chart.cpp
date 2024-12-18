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

std::tuple<QDateTime, QDateTime, double, double> PollutantTrendLineChart::getAxisBounds() {
    double min_secs = std::numeric_limits<double>::max();
    double max_secs = 0;
    double min_y = std::numeric_limits<double>::max();
    double max_y = 0;

    for (const auto& series : pollutant_series) {
        for (auto p : series->points()) {
            min_secs = qMin(min_secs, p.x());
            max_secs = qMax(max_secs, p.x());
            min_y = qMin(min_y, p.y());
            max_y = qMax(max_y, p.y());
        }
    }

    QDateTime min_date = QDateTime();
    min_date.setMSecsSinceEpoch((qint64)min_secs);
    QDateTime max_date = QDateTime();
    max_date.setMSecsSinceEpoch((qint64)max_secs);

    QDateTime test = QDateTime();
    test.setSecsSinceEpoch(0);

    qDebug() << (int)min_secs << min_date << test;

    return {min_date, max_date, min_y, max_y};
}

void PollutantTrendLineChart::setAxes()
{
    for (auto axis : axes()) {
        removeAxis(axis);
    }

    const auto bounds = getAxisBounds();

    auto axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Date");
    axisX->setRange(std::get<0>(bounds), std::get<1>(bounds));
    addAxis(axisX, Qt::AlignBottom);

    auto axisY = new QValueAxis;
    axisY->setLabelFormat("%.2f");
    axisY->setTitleText("Result");
    axisY->setRange(std::get<2>(bounds), std::get<3>(bounds));
    addAxis(axisY, Qt::AlignLeft);

    for (auto series : pollutant_series) {
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }
}
