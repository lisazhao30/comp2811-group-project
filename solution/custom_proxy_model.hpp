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
    void setAllowedPollutants(const QStringList &pollutants);
    void setPollutantFilter(const QString &text);
    void setLocationFilter(const QString &text);
    void setWaterBodyFilter(const QString &text);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    bool dateInRange(const QDate &date) const;

    QRegularExpression pollutantFilterRegex; 
    QRegularExpression locationFilterRegex;
    QRegularExpression waterBodyFilterRegex;
    QDate minDate;
    QDate maxDate;
    QStringList allowedPollutants;
};