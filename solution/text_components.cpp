#include "text_components.hpp"

TextComponents::TextComponents(QWidget* parent): QWidget(parent)
{
    textLayout = new QVBoxLayout(this);
}

void TextComponents::addHeaderText(const QString& text)
{
    QFont font("Satoshi", 60, QFont::Bold);
    QLabel* header = createLabel(text, font, "color: black;");
    textLayout->addWidget(header);
}

void TextComponents::addHeader2Text(const QString& text)
{
    QFont font("Satoshi", 40, QFont::Bold);
    QLabel* header = createLabel(text, font, "color: black;");
    textLayout->addWidget(header);
}

void TextComponents::addParagraphText(const QString& text)
{
    QFont font("Satoshi", 30, QFont::Medium);
    QLabel* header = createLabel(text, font, "color: black;");
    textLayout->addWidget(header);
}

QLabel* TextComponents::createLabel(const QString& text, const QFont& font, const QString& styleSheet) {
    QLabel* label = new QLabel(text, this);
    label->setFont(font);               
    label->setStyleSheet(styleSheet);    
    return label;
}