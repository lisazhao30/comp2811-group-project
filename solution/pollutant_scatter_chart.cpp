#include "pollutant_scatter_chart.hpp"
#include <iostream>

PollutantScatterSeries::PollutantScatterSeries(
    const QString& pollutant,
    QAbstractItemModel* model
    )
{
    timeSinceEpochProxyModel = new WaterSampleTableTimeSinceEpochProxy(this);
    timeSinceEpochProxyModel->setSourceModel(model);

    // create proxy model for data
    filterProxyModel = new QSortFilterProxyModel(this);
    filterProxyModel->setSourceModel(timeSinceEpochProxyModel);
    filterProxyModel->setFilterRegularExpression('^' + pollutant + '$');
    filterProxyModel->setFilterKeyColumn(5);
    filterProxyModel->sort(4);

    // create a scatter series
    scatterSeries = new QScatterSeries();
    scatterSeries->setName(pollutant);
    scatterSeries->setMarkerSize(8); // Set marker size

    // iterate through each data point
    for (int row = 0; row < filterProxyModel->rowCount(); ++row) {
        QModelIndex dateIndex = filterProxyModel->index(row, 4); 
        QModelIndex resultIndex = filterProxyModel->index(row, 9);  

        QVariant dateData = dateIndex.data();
        QVariant resData = resultIndex.data();

        if (dateData.isValid() && resData.isValid()) {
            // convert everything to proper timestamp and res
            qlonglong timestamp = dateData.toLongLong();  
            QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(timestamp); 

            // qDebug() << "Row:" << row << "Date:" << dateTime.toString("yyyy-MM-dd hh:mm:ss");

            // add data to scatter series
            scatterSeries->append(dateTime.toMSecsSinceEpoch(), resData.toDouble());
            
            // add compliance colours
            double result = resData.toDouble();
            QColor pointColor;

            // picked an arbitrary value for green and yellow
            if (result <= 30) {
                pointColor = QColor("green");  // Compliant
            } else if (result > 30 && result <= 50) {
                pointColor = QColor("yellow");  // Warning
            } else {
                pointColor = QColor("red");  // Non-compliant
            }

            scatterSeries->setBrush(pointColor);  
        } else {
            // qDebug() << "Invalid date or result data at row:" << row;
        }
    }

    // qDebug() << "points appended to scatter series: " << scatterSeries->count();
}

PollutantScatterChart::PollutantScatterChart(
    const QString& pollutant,
    QAbstractItemModel* model,
    QGraphicsItem *parent
    ): QChart(parent)
{
    legend()->hide();
    setAnimationOptions(QChart::AllAnimations);
    pollutant_series = new PollutantScatterSeries(pollutant, model);
    addSeries(pollutant_series->getScatterSeries());  
    setAxes();
}

void PollutantScatterChart::setAxes()
{
    for (auto axis : axes()) {
        removeAxis(axis);
    }

    auto axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText(tr("Date"));

    QDateTime minDate = QDateTime::fromMSecsSinceEpoch(pollutant_series->getScatterSeries()->at(0).x());
    QDateTime maxDate = QDateTime::fromMSecsSinceEpoch(pollutant_series->getScatterSeries()->at(0).x());
    for (int i = 1; i < pollutant_series->getScatterSeries()->count(); ++i) {
        QDateTime currentDate = QDateTime::fromMSecsSinceEpoch(pollutant_series->getScatterSeries()->at(i).x());
        if (currentDate < minDate) minDate = currentDate;
        if (currentDate > maxDate) maxDate = currentDate;
    }

    // try to add padding to axis (not working)
    int paddingDays = 14; 
    minDate = minDate.addDays(-paddingDays);
    maxDate = maxDate.addDays(paddingDays);

    axisX->setRange(minDate, maxDate);
    addAxis(axisX, Qt::AlignBottom);
    pollutant_series->attachAxis(axisX);

    auto axisY = new QValueAxis;
    axisY->setLabelFormat("%.2f");
    axisY->setTitleText(tr("Result"));

    double minY = pollutant_series->getScatterSeries()->at(0).y();
    double maxY = pollutant_series->getScatterSeries()->at(0).y();
    for (int i = 1; i < pollutant_series->getScatterSeries()->count(); ++i) {
        double currentY = pollutant_series->getScatterSeries()->at(i).y();
        if (currentY < minY) minY = currentY;
        if (currentY > maxY) maxY = currentY;
    }
    
    // padding still doesn't work
    axisY->setRange(minY - 10, maxY + 10);  
    addAxis(axisY, Qt::AlignLeft);
    pollutant_series->attachAxis(axisY);
}
