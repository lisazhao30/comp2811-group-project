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
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); 
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
}

// reusable font components
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

QLabel* Page::addSubtitleText(const QString& text)
{
    QFont font("Satoshi", 30, QFont::Medium);
    QLabel* subtitle = createLabel(text, font, "color: black;");
    pageLayout->addWidget(subtitle);
    return subtitle;
}

QLabel* Page::addParagraphText(const QString& text)
{
    QFont font("Satoshi", 16);
    QLabel* paragraph = createLabel(text, font, "color: black");
    pageLayout->addWidget(paragraph);
    return paragraph;
}

QLabel* Page::addFooterCredits()
{
    QFont font("Satoshi", 12);
    QLabel* credits = createLabel("Made with ❤️ by University of Leeds Students", font, "color: black");
    credits->setAlignment(Qt::AlignCenter); 
    // place at bottom of page
    pageLayout->addItem(new QSpacerItem(0, 60, QSizePolicy::Minimum, QSizePolicy::Expanding));
    pageLayout->addWidget(credits, 0, Qt::AlignCenter);
    return credits;
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

QHBoxLayout* Page::createHelpInfoPopup(const QString& labelText, const QString& popupText)
{
    QLabel* label = new QLabel(labelText, this);
    label->setStyleSheet("color: black;");

    QPushButton* infoIcon = new QPushButton(this);
    infoIcon->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/statics/question.png"));
    infoIcon->setFixedSize(20, 20); 
    infoIcon->setStyleSheet("border: none;"); 
    infoIcon->setToolTip("Click for more information");

    connect(infoIcon, &QPushButton::clicked, this, [this, popupText]() {
        showPopup(popupText);
    });
    
    // place icon and text label beside one another
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addWidget(infoIcon);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(5);
    layout->setAlignment(Qt::AlignLeft);

    return layout;
}

void Page::modelUpdated() {
    // Do nothing
}

// slot to show popup
void Page::showPopup(const QString& text)
{
    QMessageBox::information(this, tr("Information"), text);
}
