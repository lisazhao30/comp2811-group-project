#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

#include "../table_model.hpp"

class Page: public QWidget
{
    Q_OBJECT

    public:
        Page(WaterSampleTableModel* model, QWidget* parent = nullptr);

        void addHeaderText(const QString& text);
        void addHeader2Text(const QString& text);
        void addParagraphText(const QString& text);
        void addWidget(QWidget* widget);

    protected:
        QVBoxLayout* pageLayout;
        QLabel* createLabel(const QString& text, const QFont& font, const QString& styleSheet);

    public slots:
        void modelUpdated();
};
