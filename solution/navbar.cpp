#include "navbar.hpp"

NavBar::NavBar(QWidget* parent): QWidget(parent)
{
    navBarLayout = new QHBoxLayout(this);

    setMinimumSize(0, 50);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);

    tabBar = new QTabBar(this);
    tabBar->setDrawBase(false);

    // set tab text colour to black
    tabBar->setStyleSheet("color: black;");

    navBarLayout->addWidget(tabBar);
}

void NavBar::addTab(QStackedWidget* pages, const QString& label)
{
    tabBar->addTab(label);
    connect(tabBar, SIGNAL(currentChanged(int)), pages, SLOT(setCurrentIndex(int)));
}
