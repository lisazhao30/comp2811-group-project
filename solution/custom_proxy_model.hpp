#pragma once

#include <QSortFilterProxyModel>
#include <QDate>

class CustomProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    CustomProxyModel(QObject *parent = nullptr);

    void setFilterMinimumDate(const QDate &date);
    void setFilterMaximumDate(const QDate &date);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    bool dateInRange(const QDate &date) const;

    QDate minDate;
    QDate maxDate;
};