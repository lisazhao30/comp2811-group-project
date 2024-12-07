#pragma once

#include <QLineSeries>
#include <QString>
#include <QChart>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QAbstractSeries>
#include "table_model.hpp"
#include <QVXYModelMapper>
#include <QSortFilterProxyModel>

class PollutantTrendLineSeries: public QLineSeries
{
    public:
        PollutantTrendLineSeries(const QString& pollutant, WaterSampleTableModel* model);

    private:
        WaterSampleTableTimeSinceEpochProxy* timeSinceEpochProxyModel;
        QSortFilterProxyModel* filterProxyModel;
        QVXYModelMapper* mapper;
};

class PollutantTrendLineChart: public QChart
{
    public:
        PollutantTrendLineChart(const QString& pollutant, WaterSampleTableModel* model, QGraphicsItem *parent = nullptr);
        void setAxes();
    
    private:
        PollutantTrendLineSeries* pollutant_series;
};