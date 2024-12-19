#pragma once

#include <QString>
#include <QChart>
#include <QScatterSeries>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QGraphicsItem>
#include <QAbstractItemModel>
#include <QColor>
#include <QSortFilterProxyModel>
#include <QLineSeries>
#include <QAbstractSeries>
#include <QAbstractItemModel>

#include "table_model.hpp"

class PollutantScatterSeries: public QLineSeries
{
public:
    PollutantScatterSeries(const QString& pollutant, QAbstractItemModel* model);

    void updateComplianceColors();
    QScatterSeries* getScatterSeries() const {
        return scatterSeries;
    }

private:
    WaterSampleTableTimeSinceEpochProxy* timeSinceEpochProxyModel;
    QSortFilterProxyModel* filterProxyModel;
    QScatterSeries *scatterSeries;
};

class PollutantScatterChart : public QChart
{
    Q_OBJECT

public:
    PollutantScatterChart(
        const QString &pollutant,
        QAbstractItemModel *model,
        QGraphicsItem *parent = nullptr
        );

    void setAxes();

private:
    PollutantScatterSeries* pollutant_series;
};

