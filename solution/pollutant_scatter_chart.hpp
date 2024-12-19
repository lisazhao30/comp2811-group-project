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
    PollutantScatterSeries(const QString& pollutant, QAbstractItemModel* model, 
        QChart* chart, double greenMax, double yellowMin, double yellowMax, bool isReverseOrder);

    void updateComplianceColors();
    QScatterSeries* getScatterSeries() const {
        return scatterSeries;
    }

private:
    WaterSampleTableTimeSinceEpochProxy* timeSinceEpochProxyModel;
    QSortFilterProxyModel* filterProxyModel;
    QScatterSeries *scatterSeries;
    QChart* chart;
};

class PollutantScatterChart : public QChart
{
    Q_OBJECT

public:
    PollutantScatterChart(
        const QString &pollutant,
        QAbstractItemModel *model,
        double greenMax,
        double yellowMin,
        double yellowMax,
        bool isReverseOrder,
        QGraphicsItem *parent = nullptr
        );

    void setAxes();
    void setVerticalAxisTitle(const QString &title);

private:
    PollutantScatterSeries* pollutant_series;
    QString verticalTitle = tr("Result");
};

