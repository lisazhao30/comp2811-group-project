#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>

class TextComponents: public QWidget
{
    public:
        TextComponents(QWidget* parent = nullptr);

        void addHeaderText(const QString& text);
        void addHeader2Text(const QString& text);
        void addSubtitleText(const QString& text);
        void addParagraphText(const QString& text);
        
    private:
        QVBoxLayout* textLayout;
        QLabel* createLabel(const QString& text, const QFont& font, const QString& styleSheet);
};
