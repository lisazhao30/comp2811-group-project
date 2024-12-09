#include "data_page.hpp"

DataPage::DataPage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    addHeader2Text("Data Page");

    // add table
    QTableView* table = new QTableView(this);

    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    table->setModel(proxyModel);

    QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    table->setFont(tableFont);

    addWidget(table);
}
