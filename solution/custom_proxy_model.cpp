#include "custom_proxy_model.hpp"
#include <iostream>

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

// filter for pollutants
void CustomProxyModel::setAllowedPollutants(const QStringList &pollutants)
{
    allowedPollutants = pollutants;
    invalidateFilter();
}

bool CustomProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex dateIndex = sourceModel()->index(sourceRow, 4, sourceParent);
    QModelIndex locationIndex = sourceModel()->index(sourceRow, 3, sourceParent);
    QModelIndex pollutantIndex = sourceModel()->index(sourceRow, 5, sourceParent); 
    QModelIndex waterBodyIndex = sourceModel()->index(sourceRow, 11, sourceParent);
    
    QDate date = sourceModel()->data(dateIndex).toDate();
    QString pollutant = sourceModel()->data(pollutantIndex).toString();

    // only filter if allowedPollutants array is not empty
    bool pollutantFilter = allowedPollutants.isEmpty() || allowedPollutants.contains(pollutant, Qt::CaseInsensitive);

    // some hardcode to see whether pollutant or location filter is active
    bool pollutantMatch = true; 
    if (!pollutantFilterRegex.pattern().isEmpty()) {
        pollutantMatch = pollutant.contains(pollutantFilterRegex);  
    }

    bool locationMatch = true;
    if (!locationFilterRegex.pattern().isEmpty()) { 
        locationMatch = sourceModel()->data(locationIndex).toString().contains(locationFilterRegex);  
    }

    bool waterBodyTypeMatch = true;
    if (!waterBodyFilterRegex.pattern().isEmpty()) {
        waterBodyTypeMatch = sourceModel()->data(locationIndex).toString().contains(waterBodyFilterRegex);
    }

    // std::cout << "Pollutant filter pattern: " << pollutantFilterRegex.pattern().toStdString() << std::endl;
    // std::cout << "Location filter pattern: " << locationFilterRegex.pattern().toStdString() << std::endl;
    // std::cout << "pollutantFilter: " << pollutantFilter << std::endl;
    // std::cout << "locationMatch: " << locationMatch << std::endl;
    // std::cout << "dateInRange: " << dateInRange(date) << std::endl;
    // std::cout << "pollutantMatch: " << pollutantMatch << std::endl;

    return pollutantFilter && locationMatch && waterBodyTypeMatch && dateInRange(date) && pollutantMatch;
}

bool CustomProxyModel::dateInRange(const QDate &date) const
{
    return (!minDate.isValid() || date >= minDate) && (!maxDate.isValid() || date <= maxDate);
}

void CustomProxyModel::setPollutantFilter(const QString &text)
{
    pollutantFilterRegex.setPattern(text);
    pollutantFilterRegex.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
    invalidateFilter(); 
}

void CustomProxyModel::setLocationFilter(const QString &text)
{
    locationFilterRegex.setPattern(text);
    locationFilterRegex.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
    invalidateFilter(); 
}

void CustomProxyModel::setWaterBodyFilter(const QString &text)
{
    waterBodyFilterRegex.setPattern(text);
    waterBodyFilterRegex.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
    invalidateFilter(); 
}