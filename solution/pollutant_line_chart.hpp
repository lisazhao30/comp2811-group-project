#pragma once

#include <QLineSeries>
#include <QString>
#include <QChart>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QAbstractSeries>
#include <QAbstractItemModel>
#include "table_model.hpp"
#include <QList>
#include <QVXYModelMapper>
#include <QSortFilterProxyModel>

class PollutantTrendLineSeries: public QLineSeries
{
public:
    PollutantTrendLineSeries(const QString& pollutant, QAbstractItemModel* model, QObject *parent = nullptr);

private:
    WaterSampleTableTimeSinceEpochProxy* timeSinceEpochProxyModel;
    QSortFilterProxyModel* filterProxyModel;
    QVXYModelMapper* mapper;
};

class PollutantTrendLineChart: public QChart
{
public:
    PollutantTrendLineChart(const QString& pollutant, QAbstractItemModel* model, QGraphicsItem *parent = nullptr);
    PollutantTrendLineChart(QList<QString> pollutants, QAbstractItemModel* model, QGraphicsItem *parent = nullptr);
    void setVerticalAxisTitle(const QString &title);
    void setAxes();
    
private:
    std::tuple<QDateTime, QDateTime, double, double> getAxisBounds();

    QList<PollutantTrendLineSeries*> pollutant_series;
    QString verticalTitle = tr("Result");
};
