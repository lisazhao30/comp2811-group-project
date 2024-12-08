#pragma once

#include <QWidget>
#include <QTabBar>
#include <QHBoxLayout>
#include <QStackedWidget>

class NavBar: public QWidget
{
    public:
        NavBar(QWidget* parent = nullptr);
        void addTab(QStackedWidget* pages, const QString& label);
    
    private:
        QHBoxLayout* navBarLayout;
        QTabBar* tabBar;
};
