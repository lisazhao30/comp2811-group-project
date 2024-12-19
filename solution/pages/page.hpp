#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QApplication>

#include "../table_model.hpp"

class Page: public QWidget
{
    Q_OBJECT

public:
    Page(WaterSampleTableModel* model, QWidget* parent = nullptr);

    void addHeaderText(const QString& text);
    void addWidget(QWidget* widget);
    void addHorizontalLayout(QWidget* leftWidget, QWidget* rightWidget, int spacing);
    void showPopup(const QString& text);

    QLabel* addHeader2Text(const QString& text);
    QLabel* addSubtitleText(const QString& text);
    QLabel* addParagraphText(const QString& text);
    QLabel* addFooterCredits();
    QHBoxLayout* createHelpInfoPopup(const QString& labelText, const QString& popupText);

protected:
    QVBoxLayout* pageLayout;
    QLabel* createLabel(const QString& text, const QFont& font, const QString& styleSheet);

public slots:
    void modelUpdated();
};
