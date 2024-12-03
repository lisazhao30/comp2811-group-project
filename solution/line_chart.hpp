#pragma once

#include <QLineSeries>
#include <QString>
#include "table_model.hpp"
#include <QVXYModelMapper>
#include <QSortFilterProxyModel>

class PollutantTrendLineSeries: public QLineSeries
{
    public:
        PollutantTrendLineSeries(const QString& pollutant, WaterSampleTableModel& model);

    private:
        WaterSampleTableMonthDayProxy* monthDayProxyModel;
        QSortFilterProxyModel* filterProxyModel;
        QVXYModelMapper* mapper;
};