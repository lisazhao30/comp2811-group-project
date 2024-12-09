#include "page.hpp"

Page::Page(WaterSampleTableModel* model, QWidget* parent): QWidget(parent)
{
    pageLayout = new QVBoxLayout(this);
    setLayout(pageLayout);
}

void Page::addHeaderText(const QString& text)
{
    QFont font("Satoshi", 60, QFont::Bold);
    QLabel* header = createLabel(text, font, "color: black;");
    pageLayout->addWidget(header);
}

void Page::addHeader2Text(const QString& text)
{
    QFont font("Satoshi", 40, QFont::Bold);
    QLabel* header = createLabel(text, font, "color: black;");
    pageLayout->addWidget(header);
}

void Page::addParagraphText(const QString& text)
{
    QFont font("Satoshi", 30, QFont::Medium);
    QLabel* header = createLabel(text, font, "color: black;");
    pageLayout->addWidget(header);
}

void Page::addWidget(QWidget* widget)
{
    pageLayout->addWidget(widget);
}

QLabel* Page::createLabel(const QString& text, const QFont& font, const QString& styleSheet) {
    QLabel* label = new QLabel(text, this);
    label->setFont(font);               
    label->setStyleSheet(styleSheet);    
    return label;
}

void Page::modelUpdated() {
    // Do nothing
}
