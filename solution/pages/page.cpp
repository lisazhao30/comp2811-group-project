#include "page.hpp"

Page::Page(WaterSampleTableModel* model, QWidget* parent): QWidget(parent)
{
    // create the qt widget
    QWidget* contentWidget = new QWidget(this);
    pageLayout = new QVBoxLayout(contentWidget);
    contentWidget->setLayout(pageLayout);

    // create a scrollable page to view all content
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidget(contentWidget);
    scrollArea->setWidgetResizable(true); // Ensures resizing works correctly
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Optional
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);   // Optional

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
}

void Page::addHeaderText(const QString& text)
{
    QFont font("Satoshi", 60, QFont::Bold);
    QLabel* header = createLabel(text, font, "color: black;");
    pageLayout->addWidget(header);
}

QLabel* Page::addHeader2Text(const QString& text)
{
    QFont font("Satoshi", 40, QFont::Bold);
    QLabel* header = createLabel(text, font, "color: black;");
    pageLayout->addWidget(header);
    return header;
}

QLabel* Page::addParagraphText(const QString& text)
{
    QFont font("Satoshi", 30, QFont::Medium);
    QLabel* paragraph = createLabel(text, font, "color: black;");
    pageLayout->addWidget(paragraph);
    return paragraph;
}

void Page::addWidget(QWidget* widget)
{
    pageLayout->addWidget(widget);
}

// create horizontal layout for hero descriptor
void Page::addHorizontalLayout(QWidget* leftWidget, QWidget* rightWidget, int spacing)
{
    QHBoxLayout* horizontalLayout = new QHBoxLayout;        horizontalLayout->setAlignment(Qt::AlignCenter);
    horizontalLayout->addWidget(leftWidget);
    horizontalLayout->addWidget(rightWidget);
    horizontalLayout->setSpacing(spacing);

    pageLayout->addLayout(horizontalLayout);
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
