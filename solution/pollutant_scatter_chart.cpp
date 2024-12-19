#include "pollutant_scatter_chart.hpp"
#include <iostream>

PollutantScatterSeries::PollutantScatterSeries(
    const QString& pollutant,
    QAbstractItemModel* model,
    QChart* chart,
    double greenMax,      
    double yellowMin,    
    double yellowMax,
    bool isReverseOrder 
) : chart(chart) {
    timeSinceEpochProxyModel = new WaterSampleTableTimeSinceEpochProxy(this);
    timeSinceEpochProxyModel->setSourceModel(model);

    filterProxyModel = new QSortFilterProxyModel(this);
    filterProxyModel->setSourceModel(timeSinceEpochProxyModel);
    filterProxyModel->setFilterRegularExpression("^" + pollutant + "$");
    filterProxyModel->setFilterKeyColumn(5);
    filterProxyModel->sort(4);

    // colour coded series
    auto greenSeries = new QScatterSeries();
    greenSeries->setName(pollutant + QString(" (≤ %1)").arg(greenMax));
    greenSeries->setColor(QColor("green"));
    greenSeries->setMarkerSize(8);

    auto yellowSeries = new QScatterSeries();
    yellowSeries->setName(pollutant + QString(" (> %1 and ≤ %2)").arg(greenMax).arg(yellowMax));
    yellowSeries->setColor(QColor("yellow"));
    yellowSeries->setMarkerSize(8);

    auto redSeries = new QScatterSeries();
    redSeries->setName(pollutant + QString(" (> %1)").arg(yellowMax));
    redSeries->setColor(QColor("red"));
    redSeries->setMarkerSize(8);
    // qDebug() << "yellow " << yellowMax << "green " << greenMax;
    // do cases for if below threshold then set points as red
    // else if above threshold is negative then set points as red
    if (isReverseOrder) {
        for (int row = 0; row < filterProxyModel->rowCount(); ++row) {
            QModelIndex dateIndex = filterProxyModel->index(row, 4); 
            QModelIndex resultIndex = filterProxyModel->index(row, 9);  

            QVariant dateData = dateIndex.data();
            QVariant resData = resultIndex.data();

            if (dateData.isValid() && resData.isValid()) {
                qlonglong timestamp = dateData.toLongLong();
                QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(timestamp);

                double result = resData.toDouble();
                // qDebug() << "result bro " << result;
                if (result >= greenMax) {
                    greenSeries->append(dateTime.toMSecsSinceEpoch(), result);
                } else if (result >= yellowMax && result < greenMax) {
                    // qDebug() << "yellow hit ";
                    yellowSeries->append(dateTime.toMSecsSinceEpoch(), result);
                } else {
                    redSeries->append(dateTime.toMSecsSinceEpoch(), result);
                }
            } else {
                qDebug() << "Invalid date or result data at row:" << row;
            }
        }
    } else {
        for (int row = 0; row < filterProxyModel->rowCount(); ++row) {
            QModelIndex dateIndex = filterProxyModel->index(row, 4); 
            QModelIndex resultIndex = filterProxyModel->index(row, 9);  

            QVariant dateData = dateIndex.data();
            QVariant resData = resultIndex.data();

            if (dateData.isValid() && resData.isValid()) {
                qlonglong timestamp = dateData.toLongLong();
                QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(timestamp);

                double result = resData.toDouble();
                // qDebug() << "result bro " << result;
                if (result <= greenMax) {
                    greenSeries->append(dateTime.toMSecsSinceEpoch(), result);
                } else if (result > greenMax && result <= yellowMax) {
                    // qDebug() << "yellow hit ";
                    yellowSeries->append(dateTime.toMSecsSinceEpoch(), result);
                } else {
                    redSeries->append(dateTime.toMSecsSinceEpoch(), result);
                }
            } else {
                qDebug() << "Invalid date or result data at row:" << row;
            }
        }
    }

    // qDebug() << "Series count before adding: " << chart->series().count();

    chart->addSeries(greenSeries);
    chart->addSeries(yellowSeries);
    chart->addSeries(redSeries);
    // qDebug() << "Series count after adding: " << chart->series().count();
    // qDebug() << "Green series points:" << greenSeries->points();
    // qDebug() << "Yellow series points:" << yellowSeries->points();
    // qDebug() << "Red series points:" << redSeries->points();
    chart->update();

}

// Constructor for PollutantScatterChart with thresholds
PollutantScatterChart::PollutantScatterChart(
    const QString& pollutant,
    QAbstractItemModel* model,
    double greenMax,
    double yellowMin,
    double yellowMax,
    bool isReverseOrder,
    QGraphicsItem *parent
) : QChart(parent) {
    legend()->hide();
    setAnimationOptions(QChart::AllAnimations);

    pollutant_series = new PollutantScatterSeries(pollutant, model, this, greenMax, yellowMin, yellowMax, isReverseOrder);
    setAxes();
}

// manually call setAxes() again to update it
void PollutantScatterChart::setVerticalAxisTitle(const QString &title)
{
    verticalTitle = title;
    setAxes();
}

void PollutantScatterChart::setAxes() {
    for (auto axis : axes()) {
        removeAxis(axis);
    }

    auto axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText(tr("Date"));

    auto axisY = new QValueAxis;
    axisY->setLabelFormat("%.2f");
    axisY->setTitleText(verticalTitle);

    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();
    QDateTime minDate, maxDate;

    for (auto series : this->series()) {
        QScatterSeries* scatterSeries = qobject_cast<QScatterSeries*>(series);
        if (!scatterSeries || scatterSeries->count() == 0) continue;

        for (const QPointF& point : scatterSeries->points()) {
            QDateTime currentDate = QDateTime::fromMSecsSinceEpoch(point.x());
            double currentY = point.y();

            if (minDate.isNull() || currentDate < minDate) minDate = currentDate;
            if (maxDate.isNull() || currentDate > maxDate) maxDate = currentDate;

            if (currentY < minY) minY = currentY;
            if (currentY > maxY) maxY = currentY;
        }
    }

    axisX->setRange(minDate, maxDate);
    axisY->setRange(minY, maxY);

    addAxis(axisX, Qt::AlignBottom);
    addAxis(axisY, Qt::AlignLeft);

    for (auto series : this->series()) {
        QScatterSeries* scatterSeries = qobject_cast<QScatterSeries*>(series);
        if (!scatterSeries) continue;

        scatterSeries->attachAxis(axisX);
        scatterSeries->attachAxis(axisY);
    }
}