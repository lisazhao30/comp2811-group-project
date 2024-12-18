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
        // Provide a getter for scatterSeries
        QScatterSeries* getScatterSeries() const {
            return scatterSeries;
        }

    private:
        WaterSampleTableTimeSinceEpochProxy* timeSinceEpochProxyModel;
        QSortFilterProxyModel* filterProxyModel;
        QVXYModelMapper* mapper;
        QScatterSeries *scatterSeries;  // Scatter series to hold data points for the chart
        QList<QColor> pointColors;  // To store compliance colors for each data point
};

class PollutantScatterChart : public QChart
{
    Q_OBJECT

    public:
        PollutantScatterChart(
            const QString &pollutant,                // Name of the pollutant
            QAbstractItemModel *model, 
            QGraphicsItem *parent = nullptr           // The model containing data
        );

        // Optional: Set up axes (X, Y) if not done elsewhere
        void setAxes();

    private:
        PollutantScatterSeries* pollutant_series;  // Pollutant trend series for this chart
};

