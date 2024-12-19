#include "data_page.hpp"

DataPage::DataPage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    addHeader2Text(tr("Data Page"));

    // add filter input
    filterInput = new QLineEdit();
    filterInput->setPlaceholderText(tr("Filter..."));
    connect(filterInput, SIGNAL(textChanged(const QString&)), this, SLOT(applyFilter(const QString&)));
    addWidget(filterInput);

    // create filter proxy model
    filterProxyModel = new QSortFilterProxyModel(this);
    filterProxyModel->setSourceModel(model);
    filterProxyModel->setFilterKeyColumn(-1);
    filterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    // add table
    QTableView* table = new QTableView(this);
    table->setModel(filterProxyModel);

    QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    table->setFont(tableFont);

    addWidget(table);
}

void DataPage::applyFilter(const QString& text) {
    filterProxyModel->setFilterFixedString(text);
}
