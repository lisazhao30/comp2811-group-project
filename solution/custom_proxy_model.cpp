#include "custom_proxy_model.hpp"

CustomProxyModel::CustomProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}
void CustomProxyModel::setFilterMinimumDate(const QDate &date)
{
    minDate = date;
    invalidateFilter();
}

void CustomProxyModel::setFilterMaximumDate(const QDate &date)
{
    maxDate = date;
    invalidateFilter();
}

bool CustomProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex dateIndex = sourceModel()->index(sourceRow, 4, sourceParent);
    QModelIndex locationIndex = sourceModel()->index(sourceRow, 3, sourceParent);
    QDate date = sourceModel()->data(dateIndex).toDate();
    return sourceModel()->data(locationIndex).toString().contains(filterRegularExpression()) && dateInRange(date);
}

bool CustomProxyModel::dateInRange(const QDate &date) const
{
    return (!minDate.isValid() || date >= minDate) && (!maxDate.isValid() || date <= maxDate);
}