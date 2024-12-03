#pragma once

#include <QAbstractTableModel>
#include <QIdentityProxyModel>
#include "dataset.hpp"

class WaterSampleTableModel: public QAbstractTableModel
{
  public:
    WaterSampleTableModel(QObject* parent = nullptr): QAbstractTableModel(parent) {}
    void updateFromFile(const QString&);
    bool hasData() const { return dataset.size() > 0; }

    int rowCount(const QModelIndex& index) const { return dataset.size(); }
    int columnCount(const QModelIndex& index) const { return 16; }
    QVariant data(const QModelIndex&, int) const;
    QVariant headerData(int, Qt::Orientation, int) const;

  private:
    WaterDataset dataset;
};

class WaterSampleTableMonthDayProxy: public QIdentityProxyModel
{
  public:
    WaterSampleTableMonthDayProxy(QObject* parent = nullptr): QIdentityProxyModel(parent) {}
    QVariant data(const QModelIndex&, int) const override;
};